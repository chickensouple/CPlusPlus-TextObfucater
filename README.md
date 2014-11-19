This python script will take a c++ file and a text file and #define all the tokens in the c++ file as a phrase or word from the text file, this will cause your program to look like just a version of the text file

Usage: python main.py <c++ file> <text file> <name of output file you want>

Example:

python main.py tests/programs/pascal.cpp tests/text/LifesForTheLiving.txt out.cpp

pascal.cpp:

	#include <iostream>
	#define n newVar
	using namespace std;

	int* pascal(int n);

	int main() {
		int n;
		cout << "Row of Pascal numbers: ";
		cin >> n; /* 
		this is a block
		comment that spans
		several lines */int* line;
		line = pascal(n);
		for (int i = 0; i < (n+1); i++) {
			cout << line[i] << "\t";
		}
		cout << "\n";
		delete [] line;
		return 0;
	} 

	int* pascal(int n) {
		// int pointer to dynamically allocate arrays
		// for the last line of pascals and the current line
		int* line;
		int* previousline;
		line = new int[n+1];
		if (n == 0){
			// shouldn't here get here unless called with 0
			line[0] = 1;
			return line;
		} else if (n == 1) {
			line[0] = 1;
			line[1] = 1;
			return line;
		} else {
			previousline = pascal(n - 1);
			for (int i = 1; i < (n + 1); i++){
				line[i] = previousline [i - 1] + previousline[i];
			}
			line[0] = 1;
			line[n] = 1;
			delete [] previousline;
			return line;
		}
	}

LifesForTheLiving.txt

	"Life's For The Living"
	by Passenger

	Well grey clouds wrapped round the town like elastic
	Cars stood like toys made of Taiwanese plastic
	The boy laughed at the spastic dancing around in the rain
	While laundrettes cleaned clothes, high heals rub toes
	Puddles splashed huddles of bus stop crows
	Dressed in their suits and their boots well they all look the same

	I took myself down to the cafe to find all the boys lost in books and crackling vinyl
	And carved out a poem above the urinal that read
	Don't you cry for the lost
	Smile for the living
	Get what you need and give what you're given
	Life's for the living so live it
	Or you're better off dead

	While the evening pulled the moon out of it's packet
	Stars shone like buttons on an old man's jacket
	We needed a nail but we tacked it 'til it fell of the wall

	While pigeon's pecked trains, sparks flew like planes
	The rain showed the rainbows in the oil stains
	And we all had new iPhones but no one had no one to call

	And I stumbled down to the stomach of the town
	Where the widow takes memories to slowly drown
	With a hand to the sky and a mist in her eye she said
	Don't you cry for the lost
	Smile for the living
	Get what you need and give what you're given
	Life's for the living so live it
	Or you're better off dead

	Well I'm sick of this town, this blind man's forage
	They take your dreams down and stick them in storage
	You can have them back son when you've paid off your mortgage and loans
	Oh hell with this place, I'll go it my own way
	I'll stick out my thumb and I trudge down the highway
	Someday someone must be going my way home

	Till then I'll make my bed from a disused car
	With a mattress of leaves and a blanket of stars
	And I'll stitch the words into my heart with a needle and thread
	Don't you cry for the lost
	Smile for the living
	Get what you need and give what you're given
	You know life's for the living so live it
	Or you're better off dead

	Don't you cry for the lost
	Smile for the living
	Get what you need and give what you're given
	Life's for the living so live it
	Or you're better off dead

out.cpp

	#include <iostream>

	using namespace std;
	#define n newVar

	#define _Life_s_For_The int* 
	#define Living__by_Passenger pascal(int 
	#define Well_grey_clouds n); 
	#define wrapped_round_the int 
	#define town_like_elastic main() 
	#define Cars_stood_like { 
	#define toys_made_of int 
	#define Taiwanese_plastic_The n; 
	#define boy_laughed_at cout 
	#define the_spastic_dancing << 
	#define around_in_the "Row of Pascal numbers: " 
	#define rain_While_laundrettes ; 
	#define cleaned_clothes__high cin 
	#define heals_rub_toes >> 
	#define Puddles_splashed_huddles n; 
	#define of_bus_stop int* 
	#define crows_Dressed_in line; 
	#define their_suits_and line 
	#define their_boots_well = 
	#define they_all_look pascal(n); 
	#define the_same_I for 
	#define took_myself_down (int 
	#define to_the_cafe i 
	#define to_find_all = 
	#define the_boys_lost 0; 
	#define in_books_and i 
	#define crackling_vinyl_And < 
	#define carved_out_a (n+1); 
	#define poem_above_the i++) 
	#define urinal_that_read { 
	#define Don_t_you_cry cout 
	#define for_the_lost << 
	#define Smile_for_the line[i] 
	#define living_Get_what << 
	#define you_need_and "\t" 
	#define give_what_you_re ; 
	#define given_Life_s_for } 
	#define the_living_so cout 
	#define live_it_Or << 
	#define you_re_better_off "\n" 
	#define dead_While_the ; 
	#define evening_pulled_the delete 
	#define moon_out_of [] 
	#define it_s_packet_Stars line; 
	#define shone_like_buttons return 
	#define on_an_old 0; 
	#define man_s_jacket_We } 
	#define needed_a_nail int* 
	#define but_we_tacked pascal(int 
	#define it__til_it n) 
	#define fell_of_the { 
	#define wall_While_pigeon_s int* 
	#define pecked_trains__sparks line; 
	#define flew_like_planes int* 
	#define The_rain_showed previousline; 
	#define the_rainbows_in line 
	#define the_oil_stains = 
	#define And_we_all new 
	#define had_new_iPhones int[n+1]; 
	#define but_no_one if 
	#define had_no_one (n 
	#define to_call_And == 
	#define I_stumbled_down 0){ 
	#define to_the_stomach line[0] 
	#define of_the_town = 
	#define Where_the_widow 1; 
	#define takes_memories_to return 
	#define slowly_drown_With line; 
	#define a_hand_to } 
	#define the_sky_and else 
	#define a_mist_in if 
	#define her_eye_she (n 
	#define said_Don_t_you == 
	#define cry_for_the 1) 
	#define lost_Smile_for { 
	#define the_living_Get line[0] 
	#define what_you_need = 
	#define and_give_what 1; 
	#define you_re_given_Life_s line[1] 
	#define for_the_living = 
	#define so_live_it 1; 
	#define Or_you_re_better return 
	#define off_dead_Well line; 
	#define I_m_sick_of } 
	#define this_town__this else 
	#define blind_man_s_forage { 
	#define They_take_your previousline 
	#define dreams_down_and = 
	#define stick_them_in pascal(n 
	#define storage_You_can - 
	#define have_them_back 1); 
	#define son_when_you_ve for 
	#define paid_off_your (int 
	#define mortgage_and_loans i 
	#define Oh_hell_with = 
	#define this_place__I_ll 1; 
	#define go_it_my i 
	#define own_way_I_ll < 
	#define stick_out_my (n 
	#define thumb_and_I + 
	#define trudge_down_the 1); 
	#define highway_Someday_someone i++){ 
	#define must_be_going line[i] 
	#define my_way_home = 
	#define Till_then_I_ll previousline 
	#define make_my_bed [i 
	#define from_a_disused - 
	#define car_With_a 1] 
	#define mattress_of_leaves + 
	#define and_a_blanket previousline[i]; 
	#define of_stars_And } 
	#define I_ll_stitch_the line[0] 
	#define words_into_my = 
	#define heart_with_a 1; 
	#define needle_and_thread line[n] 
	#define Don_t_you_cry_ = 
	#define for_the_lost_ 1; 
	#define Smile_for_the_ delete 
	#define living_Get_what_ [] 
	#define you_need_and_ previousline; 
	#define give_what_you_re_ return 
	#define given_You_know line; 
	#define life_s_for_the } 
	#define living_so_live_it_Or_you_re_better_off_dead_Don_t_you_cry_for_the_lost_Smile_for_the_living_Get_what_you_need_and_give_what_you_re_given_Life_s_for_the_living_so_live_it_Or_you_re_better_off_dead } 

	_Life_s_For_The Living__by_Passenger Well_grey_clouds wrapped_round_the town_like_elastic 
	Cars_stood_like toys_made_of Taiwanese_plastic_The boy_laughed_at the_spastic_dancing 
	around_in_the rain_While_laundrettes cleaned_clothes__high heals_rub_toes Puddles_splashed_huddles 
	of_bus_stop crows_Dressed_in their_suits_and their_boots_well they_all_look 
	the_same_I took_myself_down to_the_cafe to_find_all the_boys_lost 
	in_books_and crackling_vinyl_And carved_out_a poem_above_the urinal_that_read 
	Don_t_you_cry for_the_lost Smile_for_the living_Get_what you_need_and 
	give_what_you_re given_Life_s_for the_living_so live_it_Or you_re_better_off 
	dead_While_the evening_pulled_the moon_out_of it_s_packet_Stars shone_like_buttons 
	on_an_old man_s_jacket_We needed_a_nail but_we_tacked it__til_it 
	fell_of_the wall_While_pigeon_s pecked_trains__sparks flew_like_planes The_rain_showed 
	the_rainbows_in the_oil_stains And_we_all had_new_iPhones but_no_one 
	had_no_one to_call_And I_stumbled_down to_the_stomach of_the_town 
	Where_the_widow takes_memories_to slowly_drown_With a_hand_to the_sky_and 
	a_mist_in her_eye_she said_Don_t_you cry_for_the lost_Smile_for 
	the_living_Get what_you_need and_give_what you_re_given_Life_s for_the_living 
	so_live_it Or_you_re_better off_dead_Well I_m_sick_of this_town__this 
	blind_man_s_forage They_take_your dreams_down_and stick_them_in storage_You_can 
	have_them_back son_when_you_ve paid_off_your mortgage_and_loans Oh_hell_with 
	this_place__I_ll go_it_my own_way_I_ll stick_out_my thumb_and_I 
	trudge_down_the highway_Someday_someone must_be_going my_way_home Till_then_I_ll 
	make_my_bed from_a_disused car_With_a mattress_of_leaves and_a_blanket 
	of_stars_And I_ll_stitch_the words_into_my heart_with_a needle_and_thread 
	Don_t_you_cry_ for_the_lost_ Smile_for_the_ living_Get_what_ you_need_and_ 
	give_what_you_re_ given_You_know life_s_for_the living_so_live_it_Or_you_re_better_off_dead_Don_t_you_cry_for_the_lost_Smile_for_the_living_Get_what_you_need_and_give_what_you_re_given_Life_s_for_the_living_so_live_it_Or_you_re_better_off_dead 


Known issues: Certain #defines in the original code file may cause errors
When the original program file is included in other files or include other files that may contain #defines, it may also cause errors
Will not work with typedef or unions

Tested with Python 2.7.6 and Python 3.4.0
