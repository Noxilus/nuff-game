#include "Maps.h"

Map::Map() :
	layout(blankLayout),
	original_layout(blankLayout),
	commonItems(noItemDrops),
	rareItems(noItemDrops),
	commonFood(noFoodDrops),
	rareFood(noFoodDrops),
	enemyList(noEnemies),
	boss(BasicEnemy),
	exits({0, 0, 0, 0}),
	name("_NO_MAP_"),
	level(0),
	forgeX(0),
	forgeY(0),
	marketX(0),
	marketY(0),
	innX(0),
	innY(0),
	numEnemies(0),
	original_numEnemies(0)
{}

Map::Map(vector<string> l, vector<Item> ci, vector<Item> ri, vector<Food> cf, vector<Food> rf, vector<Enemy> el, Enemy b, vector<int> e, string n, int lvl, int ne) :
	layout(l),
	original_layout(l),
	commonItems(ci),
	rareItems(ri),
	commonFood(cf),
	rareFood(rf),
	enemyList(el),
	boss(b),
	exits(e),
	name(n),
	level(lvl),
	forgeX(1),
	forgeY(1),
	marketX(1),
	marketY(1),
	innX(1),
	innY(1),
	numEnemies(ne),
	original_numEnemies(ne)
{}

Map::Map(vector<string> l, vector<int> e, string n, int lvl, int fx, int fy, int mx, int my, int ix, int iy, int ne, NPC* s, NPC* h, NPC* v) :
	layout(l),
	original_layout(l),
	commonItems(noItemDrops),
	rareItems(noItemDrops),
	commonFood(noFoodDrops),
	rareFood(noFoodDrops),
	enemyList(noEnemies),
	boss(BasicEnemy),
	exits(e),
	name(n),
	level(lvl),
	forgeX(fx),
	forgeY(fy),
	marketX(mx),
	marketY(my),
	innX(ix),
	innY(iy),
	numEnemies(ne),
	original_numEnemies(ne),
	smith(s),
	host(h),
	vendor(v)
{}

Map::~Map(){
	delete smith;
	delete host;
	delete vendor;
}

void Map::ResetValues(){
	layout = original_layout;
	numEnemies = original_numEnemies;
}

Map noMap = Map();
Map highashPlainsA = Map();
Map highashPlainsB = Map();
Map highashPlainsC = Map();
Map alnwick = Map();
Map alnwickForge = Map();
Map alnwickMarket = Map();
Map alnwickInn = Map();
Map testMap = Map();
Map tbcMap = Map();
vector<Map> allMaps = {};

void InitMaps(){
	InitLayouts();
	allMaps.push_back(noMap);
	highashPlainsA = Map(plainsLayoutA, plainsItems_C, plainsItems_R, plainsFood_C, plainsFood_R, plainsEnemies, BrutalOrc, {4, 3, 2}, "Highash Plains A", 1, 7);
	allMaps.push_back(highashPlainsA);
	highashPlainsB = Map(plainsLayoutB, plainsItems_C, plainsItems_R, plainsFood_C, plainsFood_R, plainsEnemies, PlainsDemon, {1}, "Highash Plains B", 1, 6);
	allMaps.push_back(highashPlainsB);
	highashPlainsC = Map(plainsLayoutC, plainsItems_C, plainsItems_R, plainsFood_C, plainsFood_R, plainsEnemies, SmallGolem, {1}, "Highash Plains C", 1, 5);
	allMaps.push_back(highashPlainsC);
	alnwick = Map(alnwickLayout, {1, 5, 6, 7, 9}, "Alnwick", 1, 4, 10, 4, 17, 3, 22, 0, &BasicNPC, &BasicNPC, &BasicNPC);
	allMaps.push_back(alnwick);
	alnwickForge = Map(forgeLayout, {0, 4}, "Alnwick Forge", 1, 2, 6, 0, 0, 0, 0, 0, &AlnwickSmith, &BasicNPC, &BasicNPC);
	allMaps.push_back(alnwickForge);
	alnwickMarket = Map(marketLayout, {0, 0, 4}, "Alnwick Market", 1, 0, 0, 1, 4, 0, 0, 0, &BasicNPC, &BasicNPC, &AlnwickVendor);
	allMaps.push_back(alnwickMarket);
	alnwickInn = Map(innLayout, {0, 0, 0, 4}, "Alnwick Inn", 1, 0, 0, 0, 0, 2, 1, 0, &BasicNPC, &AlnwickHost, &BasicNPC);
	allMaps.push_back(alnwickInn);
	testMap = Map(testLayout, plainsItems_C, plainsItems_R, plainsFood_C, plainsFood_R, plainsEnemies, BrutalOrc, {4, 3, 2}, "//=TEST=\\\\", 1, 7);
	allMaps.push_back(testMap);
	tbcMap = Map(tbcLayout, noItemDrops, noItemDrops, noFoodDrops, noFoodDrops, noEnemies, BasicEnemy, {4}, "To Be Continued...", 1, 0);
	allMaps.push_back(tbcMap);
	// vector<Map> allMaps = {noMap, highashPlainsA, highashPlainsB, highashPlainsC, alnwick, alnwickForge, alnwickMarket, alnwickInn};
}

vector<string> blankLayout = {};
vector<string> plainsLayoutA = {};
vector<string> plainsLayoutB = {};
vector<string> plainsLayoutC = {};
vector<string> alnwickLayout = {};
vector<string> forgeLayout = {};
vector<string> marketLayout = {};
vector<string> innLayout = {};
vector<string> testLayout = {};
vector<string> tbcLayout = {};

void InitLayouts(){
blankLayout =
{"##############################",
 "#                            #",
 "#                            #",
 "#                            #",
 "#                            #",
 "#                            #",
 "#                            #",
 "#                            #",
 "#                            #",
 "##############################"};

plainsLayoutA =
{"##########################33##",
 "# G #####   ####### E ####   2",
 "# # # D # #  G      #        2",
 "# # #  ## ####################",
 "# # ##E#   #   G            G#",
 "#E# G#  G                   G#",
 "# #    ##########E############",
 "# ######DE  G              ED#",
 "#@#R   B           G       ED#",
 "################111###########"};

plainsLayoutB =
{"##############################",
 "#D    #E    ####  R  ####    #",
 "#     # #   ##G    ####      #",
 "#       #    ##B#####        #",
 "#     #G####                 #",
 "#    #D# ####          ####  #",
 "#     E    #          #GGGD# #",
 "#          #         ##EE##  #",
 "#D          E         E #    #",
 "##########################11##"};

plainsLayoutC =
{"##############################",
 "1  #     E         #DGE      #",
 "1  #GGG###        # ###      #",
 "#   #D#         ##GG    #E####",
 "#    #        ####G    #     #",
 "#         ####G#D#    #      #",
 "# #### #   #         #   G   #",
 "########    #E#     #   GDG  #",
 "#R  B E E     #      #   G   #",
 "##############################"};

alnwickLayout =
{"################111###########",
 "#                            #",
 "#  #######             ###   #",
 "#  #     #             I #   #",
 "#  #  F  #             ###   #",
 "#  #     #     ##M##         #",
 "#  #######     #   #         5",
 "#              #####         5",
 "#                            #",
 "##############################"};

forgeLayout =
{"########",
 "#  S   #",
 "#      F",
 "#  C   #",
 "########"};

marketLayout =
{"####M####",
 "#       #",
 "#   V   #",
 "#########"};

innLayout =
{"######",
 "#    #",
 "I  H #",
 "#    #",
 "######"};

testLayout =
{"#####################",
 "#D E G B R# S  C  H #",
 "#D D D D D#         #",
 "# R R R R # V       #",
 "#@                  #",
 "#####################"};

tbcLayout =
{"######              ",
 "#    #              ",
 "#    #              ",
 "#    #        TO BE ",
 "#    # CONTINUED... ",
 "#    #              ",
 "1    #   THANKS FOR ",
 "1    #     PLAYING! ",
 "######              "};
}
