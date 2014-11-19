This python script will take a c++ file and a text file and 
#define all the tokens in the c++ file as a phrase or word from the text file, this will cause your program to look like just a version of the text file

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
	#define Living__Well_grey pascal(int 
	#define clouds_wrapped_round n); 
	#define the_town_like int 
	#define elastic_Cars_stood main() 
	#define like_toys_made { 
	#define of_Taiwanese_plastic int 
	#define The_boy_laughed n; 
	#define at_the_spastic cout 
	#define dancing_around_in << 
	#define the_rain_While "Row of Pascal numbers: " 
	#define laundrettes_cleaned_clothes_ ; 
	#define high_heals_rub cin 
	#define toes_Puddles_splashed >> 
	#define huddles_of_bus n; 
	#define stop_crows_Dressed int* 
	#define in_their_suits line; 
	#define and_their_boots line 
	#define well_they_all = 
	#define look_the_same pascal(n); 
	#define I_took_myself for 
	#define down_to_the (int 
	#define cafe_to_find i 
	#define all_the_boys = 
	#define lost_in_books 0; 
	#define and_crackling_vinyl i 
	#define And_carved_out < 
	#define a_poem_above (n+1); 
	#define the_urinal_that i++) 
	#define read_Don_t_you { 
	#define cry_for_the cout 
	#define lost_Smile_for << 
	#define the_living_Get line[i] 
	#define what_you_need << 
	#define and_give_what "\t" 
	#define you_re_given_Life_s ; 
	#define for_the_living } 
	#define so_live_it cout 
	#define Or_you_re_better << 
	#define off_dead_While "\n" 
	#define the_evening_pulled ; 
	#define the_moon_out delete 
	#define of_it_s_packet [] 
	#define Stars_shone_like line; 
	#define buttons_on_an return 
	#define old_man_s_jacket 0; 
	#define We_needed_a } 
	#define nail_but_we int* 
	#define tacked_it__til pascal(int 
	#define it_fell_of n) 
	#define the_wall_While { 
	#define pigeon_s_pecked_trains_ int* 
	#define sparks_flew_like line; 
	#define planes_The_rain int* 
	#define showed_the_rainbows previousline; 
	#define in_the_oil line 
	#define stains_And_we = 
	#define all_had_new new 
	#define iPhones_but_no int[n+1]; 
	#define one_had_no if 
	#define one_to_call (n 
	#define And_I_stumbled == 
	#define down_to_the_ 0){ 
	#define stomach_of_the line[0] 
	#define town_Where_the = 
	#define widow_takes_memories 1; 
	#define to_slowly_drown return 
	#define With_a_hand line; 
	#define to_the_sky } 
	#define and_a_mist else 
	#define in_her_eye if 
	#define she_said_Don_t (n 
	#define you_cry_for == 
	#define the_lost_Smile 1) 
	#define for_the_living_ { 
	#define Get_what_you line[0] 
	#define need_and_give = 
	#define what_you_re_given 1; 
	#define Life_s_for_the line[1] 
	#define living_so_live = 
	#define it_Or_you_re 1; 
	#define better_off_dead return 
	#define Well_I_m_sick line; 
	#define of_this_town_ } 
	#define this_blind_man_s else 
	#define forage_They_take { 
	#define your_dreams_down previousline 
	#define and_stick_them = 
	#define in_storage_You pascal(n 
	#define can_have_them - 
	#define back_son_when 1); 
	#define you_ve_paid_off for 
	#define your_mortgage_and (int 
	#define loans_Oh_hell i 
	#define with_this_place_ = 
	#define I_ll_go_it 1; 
	#define my_own_way i 
	#define I_ll_stick_out < 
	#define my_thumb_and (n 
	#define I_trudge_down + 
	#define the_highway_Someday 1); 
	#define someone_must_be i++){ 
	#define going_my_way line[i] 
	#define home_Till_then = 
	#define I_ll_make_my previousline 
	#define bed_from_a [i 
	#define disused_car_With - 
	#define a_mattress_of 1] 
	#define leaves_and_a + 
	#define blanket_of_stars previousline[i]; 
	#define And_I_ll_stitch } 
	#define the_words_into line[0] 
	#define my_heart_with = 
	#define a_needle_and 1; 
	#define thread_Don_t_you line[n] 
	#define cry_for_the_ = 
	#define lost_Smile_for_ 1; 
	#define the_living_Get_ delete 
	#define what_you_need_ [] 
	#define and_give_what_ previousline; 
	#define you_re_given_You return 
	#define know_life_s_for line; 
	#define the_living_so } 
	#define live_it_Or_you_re_better_off_dead_Don_t_you_cry_for_the_lost_Smile_for_the_living_Get_what_you_need_and_give_what_you_re_given_Life_s_for_the_living_so_live_it_Or_you_re_better_off_dead } 

	_Life_s_For_The Living__Well_grey clouds_wrapped_round the_town_like elastic_Cars_stood 
	like_toys_made of_Taiwanese_plastic The_boy_laughed at_the_spastic dancing_around_in 
	the_rain_While laundrettes_cleaned_clothes_ high_heals_rub toes_Puddles_splashed huddles_of_bus 
	stop_crows_Dressed in_their_suits and_their_boots well_they_all look_the_same 
	I_took_myself down_to_the cafe_to_find all_the_boys lost_in_books 
	and_crackling_vinyl And_carved_out a_poem_above the_urinal_that read_Don_t_you 
	cry_for_the lost_Smile_for the_living_Get what_you_need and_give_what 
	you_re_given_Life_s for_the_living so_live_it Or_you_re_better off_dead_While 
	the_evening_pulled the_moon_out of_it_s_packet Stars_shone_like buttons_on_an 
	old_man_s_jacket We_needed_a nail_but_we tacked_it__til it_fell_of 
	the_wall_While pigeon_s_pecked_trains_ sparks_flew_like planes_The_rain showed_the_rainbows 
	in_the_oil stains_And_we all_had_new iPhones_but_no one_had_no 
	one_to_call And_I_stumbled down_to_the_ stomach_of_the town_Where_the 
	widow_takes_memories to_slowly_drown With_a_hand to_the_sky and_a_mist 
	in_her_eye she_said_Don_t you_cry_for the_lost_Smile for_the_living_ 
	Get_what_you need_and_give what_you_re_given Life_s_for_the living_so_live 
	it_Or_you_re better_off_dead Well_I_m_sick of_this_town_ this_blind_man_s 
	forage_They_take your_dreams_down and_stick_them in_storage_You can_have_them 
	back_son_when you_ve_paid_off your_mortgage_and loans_Oh_hell with_this_place_ 
	I_ll_go_it my_own_way I_ll_stick_out my_thumb_and I_trudge_down 
	the_highway_Someday someone_must_be going_my_way home_Till_then I_ll_make_my 
	bed_from_a disused_car_With a_mattress_of leaves_and_a blanket_of_stars 
	And_I_ll_stitch the_words_into my_heart_with a_needle_and thread_Don_t_you 
	cry_for_the_ lost_Smile_for_ the_living_Get_ what_you_need_ and_give_what_ 
	you_re_given_You know_life_s_for the_living_so live_it_Or_you_re_better_off_dead_Don_t_you_cry_for_the_lost_Smile_for_the_living_Get_what_you_need_and_give_what_you_re_given_Life_s_for_the_living_so_live_it_Or_you_re_better_off_dead 


Known issues: Certain #defines in the original code file may cause errors
When the original program file is included in other files or include other files that may contain #defines, it may also cause errors
