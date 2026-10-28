#pragma once
#include <optional>
#include <unordered_set>

#include "map_renderer.h"
#include "transport_catalogue.h"
#include "svg.h"


class RequestHandler : public TransportCatalogue{
public:
    // MapRenderer понадобится в следующей части итогового проекта
    RequestHandler(TransportCatalogue& db,MapRenderer& renderer, 
    std::unordered_map<std::string, std::unordered_set<BusPtr>> bus_by_stop,
    std::unordered_map<std::string, BusPtr> bus_by_name,
    std::unordered_map<std::string, StopPtr> stop_by_name)
        : db_(db), renderer_(renderer), bus_by_stop_(bus_by_stop)
        , bus_by_name_(bus_by_name) , stop_by_name_(stop_by_name) {}


    // Возвращает информацию о маршруте (запрос Bus)
    std::optional<BusStat> GetBusStat(const std::string_view& bus_name) const;

    // Возвращает маршруты, проходящие через
    const std::unordered_set<BusPtr>& GetBusesByStop(const std::string_view& stop_name) const;



private:
    // RequestHandler использует агрегацию объектов "Транспортный Справочник" и "Визуализатор Карты"
    TransportCatalogue& db_;
    MapRenderer& renderer_;
    std::unordered_map<std::string, std::unordered_set<BusPtr>> bus_by_stop_;
    std::unordered_map<std::string, BusPtr> bus_by_name_;
    std::unordered_map<std::string, StopPtr> stop_by_name_;
    
};