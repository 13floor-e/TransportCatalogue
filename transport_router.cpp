#include "transport_router.h"
#include <string>
#include "json_builder.h"
using namespace std;


deque<StopPtr> CreatePtrStopDeque(const deque<Stop>& deq) { // указатели на остановки
	deque<StopPtr> point_deq;
	//point_deq.resize(deq.size());
	for (auto& val : deq) {
		point_deq.push_back(&val);
	}
	
	return point_deq;
}

deque<BusPtr> CreatePtrBusDeque(const deque<Bus>& deq) { // создание деки указателей автобусы
	deque<BusPtr> point_deq;
	//point_deq.resize(deq.size());
	for (auto& val : deq) {
		point_deq.push_back(&val);
	}

	return point_deq;
}


TransportRouter::TransportRouter(const TransportCatalogue& cat, SpeedAndTimeSettings s)
	: catalogue(cat)
	, settings_(move(s))
	{
	graph_ = BusGraph(cat.GetStops().size() * 2);
	FillGraphWithStops(catalogue);
	FillGraphWithBuses(catalogue);
	
	
	route_holder_ = make_unique<InternalRouter>(graph_);
}

optional<TotalRoute> TransportRouter::FindRoute(StopPtr from, StopPtr to)
{
	if (!from || !to) return nullopt;

	auto it_from = stops_vertex_ids_.find(from);
	auto it_to = stops_vertex_ids_.find(to);

	// Если остановки не найдены в маппинге — маршрута нет
	if (it_from == stops_vertex_ids_.end() || it_to == stops_vertex_ids_.end())
		return nullopt;

	
	// Пришёл - ждём
	const graph::VertexId start_id = it_from->second.in;

	// Приехал - ждём
	const graph::VertexId end_id = it_to->second.in;

	auto raw_route = route_holder_->BuildRoute(start_id, end_id);

	if (!raw_route.has_value()) return nullopt;

	TotalRoute result_items;
	result_items.total_time = raw_route->weight;

	for (const auto& edge_id : raw_route->edges) {
		// Используем const auto&, чтобы не модифицировать граф
		const auto& edge = graph_.GetEdge(edge_id);
		const auto& edge_meta = edges_info_[edge_id];

		if (holds_alternative<WaitEdgeInfo>(edge_meta)) {


			StopPtr stop_ = vertices_info_[edge.from].stop_ptr;

			result_items.total_steps.push_back(WaitItem{
				stop_,
				edge.weight
				});
		}
		else if (holds_alternative<BusEdgeInfo>(edge_meta)) {

			const auto& bus_data = get<BusEdgeInfo>(edge_meta);

			result_items.total_steps.push_back(BusItem{
				bus_data.bus_ptr,
				edge.weight,
				bus_data.span_count
				});
		}
	}

	return result_items;
}
void TransportRouter::BuildGraph(const TransportCatalogue& cat, const SpeedAndTimeSettings& set)
{
	//BusGraph G;
	//graph_ = BusGraph(cat.GetStops().size() * 2);
	size_t stops_count = cat.GetStops().size();
	for (size_t i = 0; i < stops_count; ++i) { 
		//auto s_in = G.AddEdge();
		size_t in_id = i * 2;
		size_t out_id = i * 2 + 1;
		graph_.AddEdge({
			.from = in_id,
			.to = out_id,
			.weight = set.bus_wait_time
			});

	}
}

void TransportRouter::FillGraphWithStops(const TransportCatalogue& cat)
{
	const auto& all_stops = cat.GetStops();
	size_t current_id = 0;

	// Проходим по ВСЕМ остановкам в каталоге
	for (const auto& stop : all_stops) {
		StopPtr stop_ptr = &stop; // Берем указатель на оригинальную остановку

		
		stops_vertex_ids_[stop_ptr] = { current_id, current_id + 1 };

		// 2. Заполняем vertices_info_, чтобы знать, какой остановке принадлежит вершина
		// Нам нужно заполнить две записи: для In и для Out
		vertices_info_.resize(current_id + 2); // Гарантируем размер

		vertices_info_[current_id] = { stop_ptr };     // Вершина In
		vertices_info_[current_id + 1] = { stop_ptr }; // Вершина Out

		// 3. Добавляем ребро ожидания: In -> Out
		Minutes wait_time(settings_.bus_wait_time.count());

		graph_.AddEdge({
			.from = current_id,
			.to = current_id + 1,
			.weight = wait_time
			});

		// 4. Добавляем метаданные для этого ребра (тип Wait)
		edges_info_.push_back(WaitEdgeInfo{});

		// Увеличиваем счетчик на 2 (две вершины на одну остановку)
		current_id += 2;
	}
}

void TransportRouter::FillGraphWithBuses(const TransportCatalogue& cat)
{
	auto p_bus_deq = CreatePtrBusDeque(cat.GetBuses());

		// size_t current_vertex_id = 0;

		for (const auto& bus : p_bus_deq) {
			const auto& stops = bus->stops;

			if (stops.size() < 2) {
				continue;
			}
			for (size_t i = 0; i < stops.size(); ++i) { // остановки конкретного автобуса
				int current_distance = 0;

				//auto it = stops_vertex_ids_.find(stops[i]); // отладка
				//if (it == stops_vertex_ids_.end()) {
				//	cerr << "Stop pointer is missing in stops_vertex_ids_: "
				//		<< stops[i]->name << '\n';

				// конец отладки

				for (size_t j = i + 1; j < stops.size(); ++j) {

					const int segment_distance =
						cat.GetDistanceBetweenStops(stops[j - 1], stops[j]);

					//auto it = stops_vertex_ids_.find(stops[j]); // отладка
					//if (it == stops_vertex_ids_.end()) {
					//	cerr << "Stop pointer is missing in stops_vertex_ids_: "
					//		<< stops[j]->name << '\n';
					//}
						// конец отладки
					
					if (segment_distance == -1) {
						break;
					}

					current_distance += segment_distance;

					const auto travel_time = CalculateTravelTime(current_distance);

					const auto& from_vertex =
						stops_vertex_ids_.at(stops[i]);
					const auto& to_vertex =
						stops_vertex_ids_.at(stops[j]);
					
					//if (from_vertex == to_vertex) continue;

					const size_t start = from_vertex.out; // сначала стоим
					const size_t finish = to_vertex.in; // потом едем

					if (start == finish) continue; // проверка на дубликаты

					graph_.AddEdge({
						.from = start,
						.to = finish,
						.weight = travel_time
						});

					// Для каждого добавленного ребра движения — ровно одна запись.
					edges_info_.push_back(BusEdgeInfo{
						.bus_ptr = bus,
						.span_count = j - i
						});
				}
			}
		}
	}

	json::Dict RouteRequest::Execute(TransportRouter& router) const
	{

		// 1. Пытаемся найти маршрут через обработчик
		const auto route = router.FindRoute(stop_from, stop_to);

		json::Dict response;
		response["request_id"] = id;
		
		
		//cerr << "FROM: " << stop_from->name << "\n";
		//cerr << "TO: " << stop_to->name << "\n";

		if (!route) { 

			
			response["error_message"] = string("not found");
			return response;
		}

		// 3. Если маршрут есть, считаем время и формируем items
		double total_time = 0.0;
		json::Array items;

		// Проходим по каждому шагу маршрута
		for (const auto& item : route->total_steps) {
			json::Dict item_json;

			// Используем std::visit для разбора варианта (BusItem или WaitItem)
			std::visit([&](const auto& specific_item) {
				using ItemType = std::decay_t<decltype(specific_item)>;

				if constexpr (std::is_same_v<ItemType, BusItem>) {
					item_json["type"] = string("Bus");
					item_json["bus"] = specific_item.bus->name;
					item_json["span_count"] = static_cast<int>(specific_item.span_count);
					item_json["time"] = specific_item.time.count(); // count() возвращает double для минут

					total_time += specific_item.time.count();
				}
				else if constexpr (std::is_same_v<ItemType, WaitItem>) {
					item_json["type"] = string("Wait");
					item_json["stop_name"] = specific_item.stop->name;
					item_json["time"] = specific_item.time.count();

					total_time += specific_item.time.count();
				}
				}, item);
			//ОТЛАДКА ДЛЯ ТИПА
			//cerr << "TYPE DEBUG: " << "\n";

			//if (item_json["type"] == "Bus") {
			//	cerr << "Type = Bus" << "\n";
			//}
			//else if (item_json["type"] == "Wait") {
			//	cerr << "Type = Wait" << "\n";
			//}
			//else if (item_json["type"] == "Bus") {
			//	cerr << "Type = Bus" << "\n";
			//}
			//else if (item_json["type"] == "Stop") {
			//	cerr << "Type = Stop" << "\n";
			//}
			// КОНЕЦ ОТЛАДКИ
			items.push_back(std::move(item_json));
		}

		response["total_time"] = total_time;

		//cerr << "TYPE DEBUG: " << item_json
		response["items"] = std::move(items);
		return response;
	}