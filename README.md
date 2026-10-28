Input example: 
{
   "base_requests":[
      {
         "is_roundtrip":true,
         "name":"297",
         "stops":[
            "Biryulyovo Zapadnoye",
            "Biryulyovo Tovarnaya",
            "Universam",
            "Biryusinka",
            "Apteka",
            "Biryulyovo Zapadnoye"
         ],
         "type":"Bus"
      },
      {
         "is_roundtrip":false,
         "name":"635",
         "stops":[
            "Biryulyovo Tovarnaya",
            "Universam",
            "Biryusinka",
            "TETs 26",
            "Pokrovskaya",
            "Prazhskaya"
         ],
         "type":"Bus"
      },
      {
         "is_roundtrip":false,
         "name":"828",
         "stops":[
            "Biryulyovo Zapadnoye",
            "TETs 26",
            "Biryusinka",
            "Universam",
            "Pokrovskaya",
            "Rossoshanskaya ulitsa"
         ],
         "type":"Bus"
      },
      {
         "latitude":55.574371,
         "longitude":37.6517,
         "name":"Biryulyovo Zapadnoye",
         "road_distances":{
            "Biryulyovo Tovarnaya":2600,
            "TETs 26":1100
         },
         "type":"Stop"
      },
      {
         "latitude":55.587655,
         "longitude":37.645687,
         "name":"Universam",
         "road_distances":{
            "Biryulyovo Tovarnaya":1380,
            "Biryusinka":760,
            "Pokrovskaya":2460
         },
         "type":"Stop"
      },
      {
         "latitude":55.592028,
         "longitude":37.653656,
         "name":"Biryulyovo Tovarnaya",
         "road_distances":{
            "Universam":890
         },
         "type":"Stop"
      },
      {
         "latitude":55.581065,
         "longitude":37.64839,
         "name":"Biryusinka",
         "road_distances":{
            "Apteka":210,
            "TETs 26":400
         },
         "type":"Stop"
      },
      {
         "latitude":55.580023,
         "longitude":37.652296,
         "name":"Apteka",
         "road_distances":{
            "Biryulyovo Zapadnoye":1420
         },
         "type":"Stop"
      },
      {
         "latitude":55.580685,
         "longitude":37.642258,
         "name":"TETs 26",
         "road_distances":{
            "Pokrovskaya":2850
         },
         "type":"Stop"
      },
      {
         "latitude":55.603601,
         "longitude":37.635517,
         "name":"Pokrovskaya",
         "road_distances":{
            "Rossoshanskaya ulitsa":3140
         },
         "type":"Stop"
      },
      {
         "latitude":55.595579,
         "longitude":37.605757,
         "name":"Rossoshanskaya ulitsa",
         "road_distances":{
            "Pokrovskaya":3210
         },
         "type":"Stop"
      },
      {
         "latitude":55.611717,
         "longitude":37.603938,
         "name":"Prazhskaya",
         "road_distances":{
            "Pokrovskaya":2260
         },
         "type":"Stop"
      },
      {
         "is_roundtrip":false,
         "name":"750",
         "stops":[
            "Tolstopaltsevo",
            "Rasskazovka"
         ],
         "type":"Bus"
      },
      {
         "latitude":55.611087,
         "longitude":37.20829,
         "name":"Tolstopaltsevo",
         "road_distances":{
            "Rasskazovka":13800
         },
         "type":"Stop"
      },
      {
         "latitude":55.632761,
         "longitude":37.333324,
         "name":"Rasskazovka",
         "road_distances":{
            
         },
         "type":"Stop"
      }
   ],
   "render_settings":{
      "bus_label_font_size":20,
      "bus_label_offset":[
         7,
         15
      ],
      "color_palette":[
         "green",
         [
            255,
            160,
            0
         ],
         "red"
      ],
      "height":200,
      "line_width":14,
      "padding":30,
      "stop_label_font_size":20,
      "stop_label_offset":[
         7,
         -3
      ],
      "stop_radius":5,
      "underlayer_color":[
         255,
         255,
         255,
         0.85
      ],
      "underlayer_width":3,
      "width":200
   },
   "routing_settings":{
      "bus_velocity":30,
      "bus_wait_time":2
   },
   "stat_requests":[
      {
         "from":"Rossoshanskaya ulitsa",
         "id":1,
         "to":"Biryulyovo Tovarnaya",
         "type":"Route"
      },
      {
         "from":"Biryulyovo Zapadnoye",
         "id":2,
         "to":"Prazhskaya",
         "type":"Route"
      },
      {
         "from":"Prazhskaya",
         "id":3,
         "to":"Biryulyovo Zapadnoye",
         "type":"Route"
      },
      {
         "from":"Biryulyovo Tovarnaya",
         "id":4,
         "to":"Rossoshanskaya ulitsa",
         "type":"Route"
      },
      {
         "from":"Biryulyovo Tovarnaya",
         "id":5,
         "to":"Biryusinka",
         "type":"Route"
      },
      {
         "from":"Biryusinka",
         "id":6,
         "to":"Biryulyovo Tovarnaya",
         "type":"Route"
      },
      {
         "from":"Rossoshanskaya ulitsa",
         "id":7,
         "to":"Biryulyovo Tovarnaya",
         "type":"Route"
      },
      {
         "from":"Biryulyovo Tovarnaya",
         "id":8,
         "to":"Rossoshanskaya ulitsa",
         "type":"Route"
      },
      {
         "from":"Tolstopaltsevo",
         "id":9,
         "to":"Rasskazovka",
         "type":"Route"
      },
      {
         "from":"Rasskazovka",
         "id":10,
         "to":"Tolstopaltsevo",
         "type":"Route"
      }
   ]
}

Output example:
[
    {
        "items": [
            {
                "stop_name": "Rossoshanskaya ulitsa",
                "time": 2,
                "type": "Wait"
            },
            {
                "bus": "828",
                "span_count": 2,
                "time": 11.34,
                "type": "Bus"
            },
            {
                "stop_name": "Universam",
                "time": 2,
                "type": "Wait"
            },
            {
                "bus": "635",
                "span_count": 1,
                "time": 2.76,
                "type": "Bus"
            }
        ],
        "request_id": 1,
        "total_time": 18.1
    },
    {
        "items": [
            {
                "stop_name": "Biryulyovo Zapadnoye",
                "time": 2,
                "type": "Wait"
            },
            {
                "bus": "828",
                "span_count": 1,
                "time": 2.2,
                "type": "Bus"
            },
            {
                "stop_name": "TETs 26",
                "time": 2,
                "type": "Wait"
            },
            {
                "bus": "635",
                "span_count": 2,
                "time": 10.22,
                "type": "Bus"
            }
        ],
        "request_id": 2,
        "total_time": 16.42
    },
    {
        "items": [
            {
                "stop_name": "Prazhskaya",
                "time": 2,
                "type": "Wait"
            },
            {
                "bus": "635",
                "span_count": 2,
                "time": 10.22,
                "type": "Bus"
            },
            {
                "stop_name": "TETs 26",
                "time": 2,
                "type": "Wait"
            },
            {
                "bus": "828",
                "span_count": 1,
                "time": 2.2,
                "type": "Bus"
            }
        ],
        "request_id": 3,
        "total_time": 16.42
    },
    {
        "items": [
            {
                "stop_name": "Biryulyovo Tovarnaya",
                "time": 2,
                "type": "Wait"
            },
            {
                "bus": "297",
                "span_count": 1,
                "time": 1.78,
                "type": "Bus"
            },
            {
                "stop_name": "Universam",
                "time": 2,
                "type": "Wait"
            },
            {
                "bus": "828",
                "span_count": 2,
                "time": 11.2,
                "type": "Bus"
            }
        ],
        "request_id": 4,
        "total_time": 16.98
    },
    {
        "items": [
            {
                "stop_name": "Biryulyovo Tovarnaya",
                "time": 2,
                "type": "Wait"
            },
            {
                "bus": "297",
                "span_count": 2,
                "time": 3.3,
                "type": "Bus"
            }
        ],
        "request_id": 5,
        "total_time": 5.3
    },
    {
        "items": [
            {
                "stop_name": "Biryusinka",
                "time": 2,
                "type": "Wait"
            },
            {
                "bus": "635",
                "span_count": 2,
                "time": 4.28,
                "type": "Bus"
            }
        ],
        "request_id": 6,
        "total_time": 6.28
    },
    {
        "items": [
            {
                "stop_name": "Rossoshanskaya ulitsa",
                "time": 2,
                "type": "Wait"
            },
            {
                "bus": "828",
                "span_count": 2,
                "time": 11.34,
                "type": "Bus"
            },
            {
                "stop_name": "Universam",
                "time": 2,
                "type": "Wait"
            },
            {
                "bus": "635",
                "span_count": 1,
                "time": 2.76,
                "type": "Bus"
            }
        ],
        "request_id": 7,
        "total_time": 18.1
    },
    {
        "items": [
            {
                "stop_name": "Biryulyovo Tovarnaya",
                "time": 2,
                "type": "Wait"
            },
            {
                "bus": "297",
                "span_count": 1,
                "time": 1.78,
                "type": "Bus"
            },
            {
                "stop_name": "Universam",
                "time": 2,
                "type": "Wait"
            },
            {
                "bus": "828",
                "span_count": 2,
                "time": 11.2,
                "type": "Bus"
            }
        ],
        "request_id": 8,
        "total_time": 16.98
    },
    {
        "items": [
            {
                "stop_name": "Tolstopaltsevo",
                "time": 2,
                "type": "Wait"
            },
            {
                "bus": "750",
                "span_count": 1,
                "time": 27.6,
                "type": "Bus"
            }
        ],
        "request_id": 9,
        "total_time": 29.6
    },
    {
        "items": [
            {
                "stop_name": "Rasskazovka",
                "time": 2,
                "type": "Wait"
            },
            {
                "bus": "750",
                "span_count": 1,
                "time": 27.6,
                "type": "Bus"
            }
        ],
        "request_id": 10,
        "total_time": 29.6
    }
]
