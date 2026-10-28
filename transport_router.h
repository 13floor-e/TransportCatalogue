#pragma once
#include "domain.h"
#include "graph.h" // класс, реализующий взвешенный ориентированный граф
#include "router.h" // класс, реализующий поиск кратчайшего пути во взвешенном ориентированном графе
#include "transport_catalogue.h"
#include <optional>
#include <chrono>
#include <vector>
#include <variant>
#include <unordered_map>

using Minutes = std::chrono::duration<double, std::chrono::minutes::period>;
using BusGraph = graph::DirectedWeightedGraph<Minutes>;


struct WaitItem { 
	WaitItem(StopPtr s, Minutes t) : stop(s), time(t) {}
	StopPtr stop; // Указатель на объект остановки
	Minutes time;
};

struct BusItem {
	BusItem(BusPtr b, Minutes m, size_t s) : bus(b), time(m), span_count(s) {}
	BusPtr bus; // указатель на автобус
	Minutes time;
	size_t span_count; // кол-во прошедших остановок
};

struct SpeedAndTimeSettings {
	//SpeedAndTimeSettings(int s, Minutes& min)
	//	: bus_velocity_kmh(s)
	//	, bus_wait_time(min) {}

	double bus_velocity_kmh;
	Minutes bus_wait_time;
};

struct TotalRoute {
	Minutes total_time;
	std::vector<std::variant<WaitItem, BusItem>> total_steps;

};

class TransportRouter
{
public:
	explicit TransportRouter(const TransportCatalogue& cat, SpeedAndTimeSettings s);

std::optional<TotalRoute> FindRoute(StopPtr from, StopPtr to);
void BuildGraph(const TransportCatalogue& cat, const SpeedAndTimeSettings& set);


private:
	const TransportCatalogue& catalogue;
	const SpeedAndTimeSettings& settings_;
	BusGraph graph_; // Minutes

	// Тип для внутреннего алгоритма поиска (обертка над graph::Router)
	using InternalRouter = graph::Router<Minutes>;

	//указатель, который будет хранить просчитанную таблицу путей
	std::unique_ptr<InternalRouter> route_holder_;

	Minutes CalculateTravelTime(int distance_meters) const {
		// distance_meters - расстояние между остановками в метрах (берётся из road_distances)
		// settings_.bus_velocity_kmh - скорость всех автобусов (например, 40.0)

		double speed_kmh = settings_.bus_velocity_kmh;

		// Переводим км/ч в м/мин
		// 40 км/ч = 40 * 1000 м / 60 мин = 666.66... м/мин
		double speed_m_per_min = speed_kmh * 1000.0 / 60.0;

		// Считаем время в минутах
		double time_minutes = static_cast<double>(distance_meters) / speed_m_per_min;

		return Minutes(time_minutes);
	}


	//вершины:
	struct StopVertexIds {
		graph::VertexId in; // 1.  "готов ждать"
		graph::VertexId out; // 2. "сел в автобус, уехал"
	};
	std::unordered_map<StopPtr, StopVertexIds> stops_vertex_ids_;

	// --- Информация о рёбрах ---
	struct BusEdgeInfo {
		BusPtr bus_ptr;
		size_t span_count; // сколько перегонов между остановками
	};

	struct VertexInfo {
		StopPtr stop_ptr;
	};
	std::vector<VertexInfo> vertices_info_;

	struct WaitEdgeInfo {}; // пустая структура, просто маркер, что это ребро ожидания

	// Используем variant, чтобы хранить либо данные об автобусе, либо маркер ожидания
	using EdgeInfo = std::variant<BusEdgeInfo, WaitEdgeInfo>;
	std::vector<EdgeInfo> edges_info_;

	void FillGraphWithStops(const TransportCatalogue& cat);
	void FillGraphWithBuses(const TransportCatalogue& cat);
};
struct RouteRequest {
	RouteRequest(const StopPtr f, const StopPtr t, int id_)
		: stop_from(f)
		, stop_to(t)
		, id(id_){}

	StopPtr stop_from;
	StopPtr stop_to;
	int id;

	json::Dict Execute(TransportRouter& router) const;
};
