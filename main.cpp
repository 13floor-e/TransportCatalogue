#include "json.h"
#include "domain.h"
#include "transport_catalogue.h"
#include "map_renderer.h" 
#include "json_reader.h"
#include "svg.h"

using namespace std;

int main() {

     using namespace svg;
        using namespace std;
        
        const json::Document doc_ = json::Load(cin);

        TransportCatalogue cat;
        SpeedAndTimeSettings settings{};
        JsonReader reader;
        MapRenderer render;
              
        try {
            reader.ReadBaseRequests(doc_, cat); // catalogue
            settings = reader.AddBusRouteStatsInRoute(doc_, settings); // настройки скорости
        }
        catch (out_of_range& e) {
            cerr << "Troubles in JsonReaderStdin " << e.what() << endl;
        }

        //try {
        //    TransportRouter router(cat, settings);
        //}
        //catch (out_of_range& e) {
        //    cerr << "Trouble in TransportRouter"<< e.what() << "\n";
        //}
        cat.GetBuses();
        cat.GetStops();

        const auto& root = doc_.GetRoot().AsMap();

        auto it = root.find("render_settings");

        if (it == root.end()) {
        
            cerr << "render_settings not found in root\n";
            return 0;
        }

        const auto& render_settings_json = it->second;

        RenderSettings render_settings =
        MapRenderer::FromJson(render_settings_json);
        
        MapRenderer map_renderer(render_settings);

        try {
            TransportRouter router(cat, settings);
            const json::Node result =
                reader.ReadStatRequests(doc_, router, cat, map_renderer);

            json::Print(json::Document{ result }, cout);
        }
        catch (out_of_range& e) {
            cerr << "troubles in ReadStatRequests " << e.what() << endl;
        }
        
        return 0;
}