#include <iostream>
#include <cstdlib>
#include <string>
#include <map>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

int CurrentYear = 2018;

void home();
void add_mgroup();
void add_genre();
void show_ganres();
void show_songs();
void show_mgroups();

class song;
class music_group;

map <string, int> genres; //Данный массив хранит популярность жанров (от 0 до 10)
vector <song> songs_list; //Массив всех песен
vector <music_group> music_groups;

class song {
public:
	string name;
	string genre_;
	int popularity = -1;
	int year;

	song(string n, string j, int y) {
		name = n;
		genre_ = j;
		year = y;
	}

	song(string n, string j, int y, int p) {
		name = n;
		genre_ = j;
		year = y;
		popularity = p;
	}
};

class music_group {
public:
	string name;
	vector <string> fav_janres;
	vector <song> songs;

	music_group(string n) {
		name = n;
	}
};

void home() {//начальное диалоговое окно
	int cho;
	cout << endl << "Main menu" << endl;
	cout << "1. List of groups" << endl;
	cout << "2. Top songs" << endl;
	cout << "3. Add a group" << endl;
	cout << "4. Add a genre" << endl;
	cout << "5. List of genres" << endl;
	cout << "6. Exit the program" << endl;
	cin >> cho;
	switch (cho) {
	case 1: {
		show_mgroups();
		break;
	}
	case 2: {
		show_songs();
		break;
	}
	case 3: {
		add_mgroup();
		break;
	}
	case 4: {
		add_genre();
		break;
	}
	case 5: {
		show_ganres();
		break;
	}
	case 6: {
		exit(0);
		break;
	}
	default: {
		home();
	}
	}
}

int search_mgroup(string name) {//возвращает номер музыкальной группы по названию
	for (auto it = 0; it <music_groups.size(); it++) {
		if (music_groups[it].name == name) {
			return it;
		}
	}
	return -1;
}

void add_song_to_mgroup(int b) { //диалог для добавления песни музыкальной группы
	string name;
	int i = 0;
	int cho;
	int cho2;
	cout << endl << "Enter the name of the song:" << endl;
	cin >> name;

	cout << endl << "Enter the release year of the song:" << endl;
	cin >> cho2;

	cout << endl << "Select the genre of the song:" << endl;
	for (auto it = genres.begin(); it != genres.end(); it++) {
		i++;
		cout << i << "." << it->first << endl;
	}
	cin >> cho;

	i = 0;
	for (auto it = genres.begin(); it != genres.end(); it++) {
		i++;
		if (i == cho) {
			music_groups[b].songs.push_back(song(name, it->first, cho2));
		}
	}

	for (auto it = music_groups[b].songs.begin(); it != music_groups[b].songs.end(); it++) {
		if (it->name == name) {
			int cnt = 0;
			int g_pop = 0;
			int b_pop = 0;
			int y_pop = 100 - abs(CurrentYear - it->year);
			for (auto its = music_groups[b].songs.begin(); its != music_groups[b].songs.end(); its++) {
				if (its->popularity> 0) {
					cnt++;
					g_pop = g_pop + its->popularity;
				}
			}
			if (cnt != 0) {
				g_pop = g_pop / cnt;
			}
			for (int i = 0; i <music_groups[b].fav_janres.size(); i++) {
				if (music_groups[b].fav_janres[i] == it->genre_) {
					b_pop = 100;
				}
			}

			for (auto its = genres.begin(); its != genres.end(); its++) {
				if (its->first == it->genre_) {
					if (g_pop != 0) {
						it->popularity = (g_pop + (b_pop + y_pop + 10 * its->second + rand() % 100 + 1)) / 2;
					}
					else {
						it->popularity = b_pop + y_pop + 10 * its->second + rand() % 100 + 1;
					}
				}
			}
			songs_list.push_back(song(it->name, it->genre_, it->year, it->popularity));
		}
	}

	cout << endl << "1. Add another song" << endl << "2. Home" << endl;
	cin >> cho;
	if (cho == 1) {
		add_song_to_mgroup(b);
	}
	else {
		home();
	}
}

void add_genre_to_mgroup(int b) { //диалог для добавления жанра в музыкальную группу
	int cho;
	int i = 0;
	cout << endl << "Select the genre you want to add:" << endl;
	for (auto it = genres.begin(); it != genres.end(); it++) {
		i++;
		cout << i << "." << it->first << endl;
	}
	cin >> cho;
	i = 0;
	for (auto it = genres.begin(); it != genres.end(); it++) {
		i++;
		if (i == cho) {
			music_groups[b].fav_janres.push_back(it->first);
		}
	}

	cout << endl << "1. Add another favorite genre" << endl;
	cout << "2. Add a group song" << music_groups[b].name << endl;
	cout << "3. Home" << endl;
	cin >> cho;
	if (cho == 1) {
		add_genre_to_mgroup(b);
	}
	else if (cho == 2) {
		add_song_to_mgroup(b);
	}
	else {
		home();
	}
}

void add_mgroup() {//диалог для добавления музыкальных групп
	string name;
	int cho;
	cout << endl << "Enter the name of the group:" << endl;
	cin >> name;
	music_groups.push_back(music_group(name));

	cout << endl << "1. Add a favorite genre" << endl;
	cout << "2. Add a song" << endl;
	cout << "3. Home" << endl;
	cin >> cho;
	switch (cho) {
	case 1: {
		add_genre_to_mgroup(search_mgroup(name));
		break;
	}
	case 2: {
		add_song_to_mgroup(search_mgroup(name));
		break;
	default: {
		home();
	}
	}
	}
}

void add_genre() {//добавляет жанр
	string name;
	int popularity;
	int cho;
	cout << endl << "Enter the name of the genre:" << endl;
	cin >> name;
	cout << "Enter the popularity of the genre: (from 0 to 10)" << endl;
	cin >> popularity;
	while (popularity <0 || popularity> 10) {
		cout << endl << "Wrong value. Enter genre popularity: (from 0 to 10)" << endl;
		cin >> popularity;
	}
	genres.insert(make_pair(name, popularity));
	cout << endl << "1. Add another genre" << endl << "2. Home" << endl;
	cin >> cho;
	if (cho == 1) {
		add_genre();
	}
	else {
		home();
	}
}

void show_ganres() {//выводит список жанров
	int cho;
	cout << endl << "List of genres:" << endl;
	for (auto it = genres.begin(); it != genres.end(); it++) {
		cout <<" "<< it->first << " (popularity: " << it->second <<")"<< endl;
	}
	cout <<endl<<"Press:"<<endl<< "1. Home" << endl;
	cin >> cho;
	if (cho) {
		home();
	}
}

struct pred {
	bool operator () (const song & dot1, const song & dot2)
	{
		return dot1.popularity> dot2.popularity;
	}
};

struct nov {
	bool operator () (const song & dot1, const song & dot2)
	{
		return dot1.year> dot2.year;
	}
};

void song_info(int b) {//информационный диалог
	int cho;
	cout << endl << "You chose a song:" << songs_list[b].name << endl;
	cout << "Year:" << songs_list[b].year << endl;
	cout << "Popularity:" << songs_list[b].popularity << endl;
	cout << "Genre:" << songs_list[b].genre_ << endl;
	cout << "1. Back" << endl;
	cout << "2. Home" << endl;
	cin >> cho;
	if (cho == 1) {
		show_songs();
	}
	else {
		home();
	}
}

void show_songs() {//диалог с песнями отсортированными за популярностью/новизной 
	int cho;
	cout << endl << "1. Display by popularity" << endl << "2. Display by novelty" << endl;
	cin >> cho;
	if (cho == 1) {
		cout << endl << "List of songs by popularity: (enter the song number to find out more)" << endl;
		sort(songs_list.begin(), songs_list.end(), pred());
		int i;
		for (i = 0; i != songs_list.size(); i++) {
			cout << i + 1 << "." << songs_list[i].name << " with popularity " << songs_list[i].popularity << endl;
		}
		cout << i + 1 << ". Home" << endl;
		cin >> cho;
		if (cho> 0 && cho <= i) {
			song_info(cho - 1);
		}
		else {
			home();
		}
	}
	else if (cho == 2) {
		cout << endl << "List of songs by novelty: (enter the song number to find out more)" << endl;
		sort(songs_list.begin(), songs_list.end(), nov());
		int i;
		for (i = 0; i != songs_list.size(); i++) {
			cout << i + 1 << "." << songs_list[i].name << " released in " << songs_list[i].year << endl;
		}
		cout << i + 1 << ". Home" << endl;
		cin >> cho;
		if (cho> 0 && cho <= i) {
			song_info(cho - 1);
		}
		else {
			home();
		}
	}
	else {
		home();
	}
}

void info_band(int b) {//информационный диалог
	int cho;
	cout << endl << "You chose a group:" << music_groups[b].name << endl;
	cout << "Favorite genres:" << endl;
	for (int i = 0; i <music_groups[b].fav_janres.size(); i++) {
		cout << music_groups[b].fav_janres[i] << endl;
	}
	cout << "Group songs:" << endl;
	for (int i = 0; i <music_groups[b].songs.size(); i++) {
		cout << "-"<<music_groups[b].songs[i].name << " (" << music_groups[b].songs[i].genre_ <<")"<<endl<< "Rating: " << music_groups[b].songs[i].popularity <<endl<< "Year: " << music_groups[b].songs[i].year << endl;
	}
	cout << endl << "1. Add a song" << endl << "2. Add a favorite genre" << endl << "3. Back" << endl << "4. Home" << endl;
	cin >> cho;
	if (cho == 1) {
		add_song_to_mgroup(b);
	}
	else if (cho == 2) {
		add_genre_to_mgroup(b);
	}
	else if (cho == 3) {
		show_mgroups();
	}
	else {
		home();
	}
}

void show_mgroups() {//выводит список музыкальных групп
	int cho;
	cout << endl << "List of groups: (enter the group number to find out more)" << endl;
	int i = 0;
	for (i = 0; i != music_groups.size(); i++) {
		cout << i + 1 << "." << music_groups[i].name << endl;
	}
	cout << i + 1 << ". Home" << endl;
	cin >> cho;
	if (cho> 0 && cho <= i) {
		info_band(cho - 1);
	}
	else {
		home();
	}
}

int main(int argc, const char * argv[]) {
	genres.insert(make_pair("Rock", 6));
	genres.insert(make_pair("Metal", 3));
	genres.insert(make_pair("Pop", 9));
	genres.insert(make_pair("Rap", 10));
	genres.insert(make_pair("Blues", 6));
	genres.insert(make_pair("Jazz", 4));
	genres.insert(make_pair("Country", 5));
	genres.insert(make_pair("Key-pop", 7));
	genres.insert(make_pair("House", 6));
	genres.insert(make_pair("Techno", 8));
	home();
	return 0;
}