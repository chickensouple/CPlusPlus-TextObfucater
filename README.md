storyCode
=========

have you ever written code so beautiful that it was like poetry? 
will now  you can do that all the time by macroing words from a text file to lines of your code. 
instantly turns your c++ code into an actual work of literature


Turns boring c++ code such as:
	// finds n'th row of pascal
	#include <iostream> 
	using namespace std;

	int* pascal(int n);

	int main()
	{
		int n;
		cout << "Row of Pascal numbers: ";
		cin >> n; /* 
		this is a block
		comment that spans
		several lines */int* line;
		line = pascal(n);
		for (int i = 0; i < (n+1); i++){
			cout << line[i] << "\t";
		}
		delete [] line;
		return 0;
	} 


	// REQUIRES: n >= 0
	// MODIFIES: none
	// EFFECTS: returns int pointer to array holding
	// the n'th row of pascal's triangle
	int* pascal(int n){
		// int pointer to dynamically allocate arrays
		// for the last line of pascals and the current line
		int* line;
		int* previousline;
		line = new int[n+1];
		if (n == 0){
			// shouldn't here get here unless called with 0
			line[0] = 1;
			return line;
		} else if (n == 1){
			line[0] = 1;
			line[1] = 1;
			return line;
		} else{
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
into beautiful
 	#include <iostream> 


	#define On_My using
	#define Own_From namespace
	#define Les_Miserables std;
	#define Eponine_And int*
	#define now_I_m pascal(int
	#define all_alone n);
	#define again_nowhere int
	#define to_turn main()
	#define no_one {
	#define to_go int
	#define to_without n;
	#define a_home cout
	#define without_a <<
	#define friend_without "Row of Pascal numbers: ";
	#define a_face cin
	#define to_say >>
	#define hello_to n;
	#define And_now int*
	#define the_night line;
	#define is_near line
	#define Now_I =
	#define can_make pascal(n);
	#define believe_he_s for
	#define here_Sometimes (int
	#define I_walk i
	#define alone_at =
	#define night_When 0;
	#define everybody_else i
	#define is_sleeping <
	#define I_think (n+1);
	#define of_him i++){
	#define and_then cout
	#define I_m_happy <<
	#define With_the line[i]
	#define company_I_m <<
	#define keeping_The "\t"; }
	#define city_goes delete
	#define to_bed []
	#define And_I line;
	#define can_live return
	#define inside_my 0;
	#define head_On }
	#define my_own int*
	#define Pretending_he_s pascal(int
	#define beside_me n){
	#define All_alone int*
	#define I_walk_ line;
	#define with_him int*
	#define till_morning previousline;
	#define Without_him line
	#define I_feel =
	#define his_arms new
	#define around_me int[n+1];
	#define And_when if
	#define I_lose (n
	#define my_way ==
	#define I_close 0){
	#define my_eyes line[0]
	#define And_he =
	#define has_found 1;
	#define me_In return
	#define the_rain line;
	#define the_pavement }
	#define shines_like else
	#define silver_All if
	#define the_lights (n
	#define are_misty ==
	#define in_the 1){
	#define river_In line[0]
	#define the_darkness =
	#define the_trees 1;
	#define are_full line[1]
	#define of_starlight =
	#define And_all 1;
	#define I_see return
	#define is_him line;
	#define and_me }
	#define forever_and else{
	#define forever_And previousline
	#define I_know =
	#define it_s_only pascal(n
	#define in_my -
	#define mind_That 1);
	#define I_m_talking for
	#define to_myself (int
	#define and_not i
	#define to_him =
	#define And_although 1;
	#define I_know_ i
	#define that_he <
	#define is_blind (n
	#define Still_I +
	#define say_there_s 1);
	#define a_way i++){
	#define for_us line[i]
	#define I_love =
	#define him_But previousline
	#define when_the [i
	#define night_is -
	#define over_He 1]
	#define is_gone +
	#define The_river_s previousline[i];
	#define just_a }
	#define river_Without line[0]
	#define him_The =
	#define world_around 1;
	#define me_changes line[n]
	#define The_trees =
	#define are_bare 1;
	#define and_everywhere delete
	#define The_streets []
	#define are_full_ previousline;
	#define of_strangers return
	#define I_love_ line;
	#define him_But_ }
	#define every_day_I_m_learning_All_my_life_I_ve_only_been_pretending_Without_me_His_world_would_go_on_turning_A_world_that_s_full_of_happiness_That_I_have_never_known_I_love_him_I_love_him_I_love_him_But_only_on_my_own }


	On_My Own_From Les_Miserables Eponine_And now_I_m all_alone 
	again_nowhere to_turn no_one to_go to_without 
	a_home without_a friend_without a_face to_say 
	hello_to And_now the_night is_near Now_I 
	can_make believe_he_s here_Sometimes I_walk alone_at 
	night_When everybody_else is_sleeping I_think of_him 
	and_then I_m_happy With_the company_I_m keeping_The 
	city_goes to_bed And_I can_live inside_my 
	head_On my_own Pretending_he_s beside_me All_alone 
	I_walk_ with_him till_morning Without_him I_feel 
	his_arms around_me And_when I_lose my_way 
	I_close my_eyes And_he has_found me_In 
	the_rain the_pavement shines_like silver_All the_lights 
	are_misty in_the river_In the_darkness the_trees 
	are_full of_starlight And_all I_see is_him 
	and_me forever_and forever_And I_know it_s_only 
	in_my mind_That I_m_talking to_myself and_not 
	to_him And_although I_know_ that_he is_blind 
	Still_I say_there_s a_way for_us I_love 
	him_But when_the night_is over_He is_gone 
	The_river_s just_a river_Without him_The world_around 
	me_changes The_trees are_bare and_everywhere The_streets 
	are_full_ of_strangers I_love_ him_But_ every_day_I_m_learning_All_my_life_I_ve_only_been_pretending_Without_me_His_world_would_go_on_turning_A_world_that_s_full_of_happiness_That_I_have_never_known_I_love_him_I_love_him_I_love_him_But_only_on_my_own 
by giving the program a text file.

compile with 
g++ main.cpp fileClasses.cpp -o storyCode
(disregard the program_literature.cpp)

run with
storyCode <name of .cpp file> <name of .txt file> <name of outputfile>

This currently only works with c++ and is still a work in progress.
