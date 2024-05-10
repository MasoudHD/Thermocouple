#include "thermocouple.h"

#ifdef LOOKUP_TABLE
    // K-Type Table
    const long int TC_TB_K_TYPE[TC_TB_K_TYPE_LEN] = 
    {
    -6458,-6457,-6456,-6455,-6453,-6452,-6450,-6448,-6446,-6444,
    -6441,-6438,-6435,-6432,-6429,-6425,-6421,-6417,-6413,-6408,
    -6404,-6399,-6393,-6388,-6382,-6377,-6370,-6364,-6358,-6351,
    -6344,-6337,-6329,-6322,-6314,-6306,-6297,-6289,-6280,-6271,
    -6262,-6252,-6243,-6233,-6223,-6213,-6202,-6192,-6181,-6170,
    -6158,-6147,-6135,-6123,-6111,-6099,-6087,-6074,-6061,-6048,
    -6035,-6021,-6007,-5994,-5980,-5965,-5951,-5936,-5922,-5907,
    -5891,-5876,-5861,-5845,-5829,-5813,-5797,-5780,-5763,-5747,
    -5730,-5713,-5695,-5678,-5660,-5642,-5624,-5606,-5588,-5569,
    -5550,-5531,-5512,-5493,-5474,-5454,-5435,-5415,-5395,-5374,
    -5354,-5333,-5313,-5292,-5271,-5250,-5228,-5207,-5185,-5163,
    -5141,-5119,-5097,-5074,-5052,-5029,-5006,-4983,-4960,-4936,
    -4913,-4889,-4865,-4841,-4817,-4793,-4768,-4744,-4719,-4694,
    -4669,-4644,-4618,-4593,-4567,-4542,-4516,-4490,-4463,-4437,
    -4411,-4384,-4357,-4330,-4303,-4276,-4249,-4221,-4194,-4166,
    -4138,-4110,-4082,-4054,-4025,-3997,-3968,-3939,-3911,-3882,
    -3852,-3823,-3794,-3764,-3734,-3705,-3675,-3645,-3614,-3584,
    -3554,-3523,-3492,-3462,-3431,-3400,-3368,-3337,-3306,-3274,
    -3243,-3211,-3179,-3147,-3115,-3083,-3050,-3018,-2986,-2953,
    -2920,-2887,-2854,-2821,-2788,-2755,-2721,-2688,-2654,-2620,
    -2587,-2553,-2519,-2485,-2450,-2416,-2382,-2347,-2312,-2278,
    -2243,-2208,-2173,-2138,-2103,-2067,-2032,-1996,-1961,-1925,
    -1889,-1854,-1818,-1782,-1745,-1709,-1673,-1637,-1600,-1564,
    -1527,-1490,-1453,-1417,-1380,-1343,-1305,-1268,-1231,-1194,
    -1156,-1119,-1081,-1043,-1006,-968,-930,-892,-854,-816,
    -778,-739,-701,-663,-624,-586,-547,-508,-470,-431,
    -392,-353,-314,-275,-236,-197,-157,-118,-79,-39,
    0,39,79,119,158,198,238,277,317,357,
    397,437,477,517,557,597,637,677,718,758,
    798,838,879,919,960,1000,1041,1081,1122,1163,
    1203,1244,1285,1326,1366,1407,1448,1489,1530,1571,
    1612,1653,1694,1735,1776,1817,1858,1899,1941,1982,
    2023,2064,2106,2147,2188,2230,2271,2312,2354,2395,
    2436,2478,2519,2561,2602,2644,2685,2727,2768,2810,
    2851,2893,2934,2976,3017,3059,3100,3142,3184,3225,
    3267,3308,3350,3391,3433,3474,3516,3557,3599,3640,
    3682,3723,3765,3806,3848,3889,3931,3972,4013,4054,
    4096,4138,4179,4220,4262,4303,4344,4385,4427,4468,
    4509,4550,4591,4633,4674,4715,4756,4797,4838,4879,
    4920,4961,5002,5043,5084,5124,5165,5206,5247,5288,
    5328,5369,5410,5450,5491,5532,5572,5613,5653,5694,
    5735,5775,5815,5856,5896,5937,5977,6017,6058,6098,
    6138,6179,6219,6259,6299,6339,6380,6420,6460,6500,
    6540,6580,6620,6660,6701,6741,6781,6821,6861,6901,
    6941,6981,7021,7060,7100,7140,7180,7220,7260,7300,
    7340,7380,7420,7460,7500,7540,7579,7619,7659,7699,
    7739,7779,7819,7859,7899,7939,7979,8019,8058,8099,
    8138,8178,8218,8258,8298,8338,8378,8418,8458,8499,
    8539,8579,8619,8659,8699,8739,8779,8819,8860,8900,
    8940,8980,9020,9061,9101,9141,9181,9222,9262,9302,
    9343,9383,9423,9464,9504,9545,9585,9626,9666,9707,
    9747,9788,9828,9869,9909,9950,9991,10031,10072,10113,
    10153,10194,10235,10276,10316,10357,10398,10439,10480,10520,
    10561,10602,10643,10684,10725,10766,10807,10848,10889,10930,
    10971,11012,11053,11094,11135,11176,11217,11259,11300,11341,
    11382,11423,11465,11506,11547,11588,11630,11671,11712,11753,
    11795,11836,11877,11919,11960,12001,12043,12084,12126,12167,
    12209,12250,12291,12333,12374,12416,12457,12499,12540,12582,
    12624,12665,12707,12748,12790,12831,12873,12915,12956,12998,
    13040,13081,13123,13165,13206,13248,13290,13331,13373,13415,
    13457,13498,13540,13582,13624,13665,13707,13749,13791,13833,
    13874,13916,13958,14000,14042,14084,14126,14167,14209,14251,
    14293,14335,14377,14419,14461,14503,14545,14587,14629,14671,
    14713,14755,14797,14839,14881,14923,14965,15007,15049,15091,
    15133,15175,15217,15259,15301,15343,15385,15427,15469,15511,
    15554,15596,15638,15680,15722,15764,15806,15849,15891,15933,
    15975,16017,16059,16102,16143,16186,16228,16270,16312,16355,
    16397,16439,16482,16524,16566,16608,16651,16693,16735,16778,
    16820,16862,16904,16947,16989,17031,17074,17116,17158,17201,
    17243,17285,17328,17370,17413,17455,17497,17540,17582,17624,
    17667,17709,17752,17794,17837,17879,17921,17964,18006,18049,
    18091,18134,18176,18218,18261,18303,18346,18388,18431,18473,
    18516,18558,18601,18643,18686,18728,18771,18813,18856,18898,
    18941,18983,19026,19068,19111,19154,19196,19239,19281,19324,
    19366,19409,19451,19494,19537,19579,19622,19664,19707,19750,
    19792,19835,19877,19920,19962,20005,20048,20090,20133,20175,
    20218,20261,20303,20346,20389,20431,20474,20516,20559,20602,
    20644,20687,20730,20772,20815,20857,20900,20943,20985,21028,
    21071,21113,21156,21199,21241,21284,21326,21369,21412,21454,
    21497,21540,21582,21625,21668,21710,21753,21796,21838,21881,
    21924,21966,22009,22052,22094,22137,22179,22222,22265,22307,
    22350,22393,22435,22478,22521,22563,22606,22649,22691,22734,
    22776,22819,22862,22904,22947,22990,23032,23075,23117,23160,
    23203,23245,23288,23331,23373,23416,23458,23501,23544,23586,
    23629,23671,23714,23757,23799,23842,23884,23927,23970,24012,
    24055,24097,24140,24182,24225,24267,24310,24353,24395,24438,
    24480,24523,24565,24608,24650,24693,24735,24778,24820,24863,
    24905,24948,24990,25033,25075,25118,25160,25203,25245,25288,
    25330,25373,25415,25458,25500,25543,25585,25627,25670,25712,
    25755,25797,25840,25882,25924,25967,26009,26052,26094,26136,
    26179,26221,26263,26306,26348,26390,26433,26475,26517,26560,
    26602,26644,26687,26729,26771,26814,26856,26898,26940,26983,
    27025,27067,27109,27152,27194,27236,27278,27320,27363,27405,
    27447,27489,27531,27574,27616,27658,27700,27742,27784,27826,
    27869,27911,27953,27995,28037,28079,28121,28163,28205,28247,
    28289,28332,28374,28416,28458,28500,28542,28584,28626,28668,
    28710,28752,28794,28835,28877,28919,28961,29003,29045,29087,
    29129,29171,29213,29255,29297,29338,29380,29422,29464,29506,
    29548,29589,29631,29673,29715,29757,29798,29840,29882,29924,
    29965,30007,30049,30090,30132,30174,30216,30257,30299,30341,
    30382,30424,30466,30507,30549,30590,30632,30674,30715,30757,
    30798,30840,30881,30923,30964,31006,31047,31089,31130,31172,
    31213,31255,31296,31338,31379,31421,31462,31504,31545,31586,
    31628,31669,31710,31752,31793,31834,31876,31917,31958,32000,
    32040,32082,32124,32165,32206,32247,32289,32330,32371,32412,
    32453,32494,32536,32577,32618,32659,32700,32741,32783,32824,
    32865,32906,32947,32988,33029,33070,33111,33152,33193,33234,
    33275,33316,33357,33398,33439,33480,33521,33562,33603,33644,
    33685,33726,33767,33808,33848,33889,33930,33971,34012,34053,
    34093,34134,34175,34216,34257,34297,34338,34379,34420,34460,
    34501,34542,34582,34623,34664,34704,34745,34786,34826,34867,
    34908,34948,34989,35029,35070,35110,35151,35192,35232,35273,
    35313,35354,35394,35435,35475,35516,35556,35596,35637,35677,
    35718,35758,35798,35839,35879,35920,35960,36000,36041,36081,
    36121,36162,36202,36242,36282,36323,36363,36403,36443,36484,
    36524,36564,36604,36644,36685,36725,36765,36805,36845,36885,
    36925,36965,37006,37046,37086,37126,37166,37206,37246,37286,
    37326,37366,37406,37446,37486,37526,37566,37606,37646,37686,
    37725,37765,37805,37845,37885,37925,37965,38005,38044,38084,
    38124,38164,38204,38243,38283,38323,38363,38402,38442,38482,
    38522,38561,38601,38641,38680,38720,38760,38799,38839,38878,
    38918,38958,38997,39037,39076,39116,39155,39195,39235,39274,
    39314,39353,39393,39432,39471,39511,39550,39590,39629,39669,
    39708,39747,39787,39826,39866,39905,39944,39984,40023,40062,
    40101,40141,40180,40219,40259,40298,40337,40376,40415,40455,
    40494,40533,40572,40611,40651,40690,40729,40768,40807,40846,
    40885,40924,40963,41002,41042,41081,41120,41159,41198,41237,
    41276,41315,41354,41393,41431,41470,41509,41548,41587,41626,
    41665,41704,41743,41781,41820,41859,41898,41937,41976,42014,
    42053,42092,42131,42169,42208,42247,42286,42324,42363,42402,
    42440,42479,42518,42556,42595,42633,42672,42711,42749,42788,
    42826,42865,42903,42942,42980,43019,43057,43096,43134,43173,
    43211,43250,43288,43327,43365,43403,43442,43480,43518,43557,
    43595,43633,43672,43710,43748,43787,43825,43863,43901,43940,
    43978,44016,44054,44092,44130,44169,44207,44245,44283,44321,
    44359,44397,44435,44473,44512,44550,44588,44626,44664,44702,
    44740,44778,44816,44853,44891,44929,44967,45005,45043,45081,
    45119,45157,45194,45232,45270,45308,45346,45383,45421,45459,
    45497,45534,45572,45610,45647,45685,45723,45760,45798,45836,
    45873,45911,45948,45986,46024,46061,46099,46136,46174,46211,
    46249,46286,46324,46361,46398,46436,46473,46511,46548,46585,
    46623,46660,46697,46735,46772,46809,46847,46884,46921,46958,
    46995,47033,47070,47107,47144,47181,47218,47256,47293,47330,
    47367,47404,47441,47478,47515,47552,47589,47626,47663,47700,
    47737,47774,47811,47848,47884,47921,47958,47995,48032,48069,
    48105,48142,48179,48216,48252,48289,48326,48363,48399,48436,
    48473,48509,48546,48582,48619,48656,48692,48729,48765,48802,
    48838,48875,48911,48948,48984,49021,49057,49093,49130,49166,
    49202,49239,49275,49311,49348,49384,49420,49456,49493,49529,
    49565,49601,49637,49674,49710,49746,49782,49818,49854,49890,
    49926,49962,49998,50034,50070,50106,50142,50178,50214,50250,
    50286,50322,50358,50393,50429,50465,50501,50537,50572,50608,
    50644,50680,50715,50751,50787,50822,50858,50894,50929,50965,
    51000,51036,51071,51107,51142,51178,51213,51249,51284,51320,
    51355,51391,51426,51461,51497,51532,51567,51603,51638,51673,
    51708,51744,51779,51814,51849,51885,51920,51955,51990,52025,
    52060,52095,52130,52165,52200,52235,52270,52305,52340,52375,
    52410,52445,52480,52515,52550,52585,52620,52654,52689,52724,
    52759,52794,52828,52863,52898,52932,52967,53002,53037,53071,
    53106,53140,53175,53210,53244,53279,53313,53348,53382,53417,
    53451,53486,53520,53555,53589,53623,53658,53692,53727,53761,
    53795,53830,53864,53898,53932,53967,54001,54035,54069,54104,
    54138,54172,54206,54240,54274,54308,54343,54377,54411,54445,
    54479,54513,54547,54581,54615,54649,54683,54717,54751,54785,
    54819,54852,54886
    };
#endif