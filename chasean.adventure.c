/*
 Andy Chase
 chasean


MY IMPLEMENTATION USES (EMOJI): UNICODE CODEPOINTS BETWEEN U+1F3E0 AND U+1F3E9.
IF YOUR TERMINAL DOES NOT SUPPORT THESE
CODEPOINTS GRAPHICALLY THE PROGRAM MAY BE DIFFICULT TO USE.


I used the prototype-first method for building this assignment.
I drafted the solution in a seperate prototype.py and ported the app to c.

I followed the prototype-first method for the following reasons:

* I've never used the prototype-first method and I wanted to try it
* I have more practice in python than in c so I wanted to think through the problem in a familiar language
* The spec was clear and static
* This assignment had basically two parts:
- Figuring out the solution
- Figuring out how to actually write the solution in c
 (so it makes sense to figure out the solution in a higher-level language)

How I felt about the prototype-first method:

 Overall it felt longer, but I liked it because I was able to build out a solution
 and get a really strong feeling for its correctness before I dove in and did the implementation.
 (Honestly it may have overall taken longer to start in c first, but it did FEEL longer)

 It gave me a strong structure to start with which I liked and allowed me to just bypass any "writer's block" or
 distractions I might have had with minor c details starting in c. In that way I think it was less risky
 time-wise to start an implementation in python first.

 "Computer-runnable pseudo-code" <- I definitely got that impression. I was also able to get a sense of what my
 data structures should look like while running so that was a huge plus while debugging.



 */
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <ctype.h>


#define RANDRANGE(a, b)           (rand() % (b-a)) + a
// Configuration
#define dir_name_format "chasean.rooms.%d"

enum RoomType {
    MID_ROOM = 0, START_ROOM, END_ROOM
};
const char *room_types[] = {"MID_ROOM", "START_ROOM", "END_ROOM"};
const char *room_names[] = {"\xF0\x9F\x8F\xA0", "\xF0\x9F\x8F\xA1", "\xF0\x9F\x8F\xA2", "\xF0\x9F\x8F\xA3",
                            "\xF0\x9F\x8F\xA4", "\xF0\x9F\x8F\xA5", "\xF0\x9F\x8F\xA6"};

#define NUMBER_OF_ROOMS 7
#define CONNECTIONS_MIN 3
#define CONNECTIONS_MAX 6
const char *room_connections[NUMBER_OF_ROOMS][NUMBER_OF_ROOMS];
int room_connections_sizes[NUMBER_OF_ROOMS];

// Configuration: Strings
#define room_file_format_header "ROOM NAME: %s\n"
#define room_file_format_footer "ROOM TYPE: %s\n"
#define room_connection_format "CONNECTION %d: %s\n"
#define error_msg "\nHUH? I DON'T UNDERSTAND THAT ROOM. TRY AGAIN.\n\n"
#define prompt_header "CURRENT LOCATION: %s\nPOSSIBLE CONNECTIONS: "
#define prompt_footer ".\nWHERE TO? > "
#define winning_message "YOU HAVE FOUND THE END ROOM. CONGRATULATIONS!\n"\
"YOU TOOK %d STEPS. YOUR PATH TO VICTORY WAS:\n"\
"%s"

// Other helper variables
int steps = 0;
int start_room = 0;
int end_room = 0;

#define BUF_SIZE 10000
char room_path_buffer[BUF_SIZE];
char buf[BUF_SIZE];
char dir_name[36];

//       External Vendor functions
// -------------------------
// Helper Shuffle Function
// From: http://stackoverflow.com/a/6127606
void shuffle(const char **array, size_t n) {
    if (n > 1) {
        size_t i;
        for (i = 0; i < n - 1; i++) {
            size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
            const char *t = array[j];
            array[j] = array[i];
            array[i] = t;
        }
    }
}

// Helper Strip Function
// From: http://stackoverflow.com/a/7775172
void strip(char *buf) { for (int i = 0, j = 0; (buf[j] = buf[i]); j += !isspace(buf[i++])); }

// -------------------------

// Converts a room name to its index in the room_index
int room_name_to_room_index(const char *key) {
    int i;
    for (i = 0; i < NUMBER_OF_ROOMS; i++) {
        if (strcmp(key, room_names[i]) == 0)
            return i;
    }
    return -1;
}

// Checks the room_connections array for certain room name string in a particular room index
int in_room_connections(const char *test_room, int room_index) {
    int i;
    for (i = 0; i < room_connections_sizes[room_index]; i++)
        if (strcmp(room_connections[room_index][i], test_room) == 0)
            return 1;
    return 0;
}

// Generates room_connections array randomly
// based on a shuffled room_names and its own random number_of_connections in each room
void build_room_connections() {
    int this_room_index = 0;
    const char **rooms_left = room_names;
    int rooms_left_number = NUMBER_OF_ROOMS;
    for (this_room_index = 0; this_room_index < NUMBER_OF_ROOMS; this_room_index++) {
        const char *this_room = room_names[this_room_index];
        rooms_left++;
        rooms_left_number--;
        int number_of_connections = RANDRANGE(CONNECTIONS_MIN, CONNECTIONS_MAX);

        int i;
        for (i = 0; i < rooms_left_number; i++) {
            if (i >= number_of_connections)
                break;
            const char *room = rooms_left[i];
            if (!in_room_connections(room, this_room_index)) {
                int other_room_index = room_name_to_room_index(room);
                assert(other_room_index != -1);
                room_connections[this_room_index][room_connections_sizes[this_room_index]++] = room;
                if (!in_room_connections(this_room, other_room_index))
                    room_connections[other_room_index][room_connections_sizes[other_room_index]++] = this_room;
            }
        }
    }
}

// Given a file, a room_name, and a room_type print room data to that file
void build_a_room(FILE *f, const char *room_name, enum RoomType room_type) {
    fprintf(f, room_file_format_header, room_name);
    const char **const connections = room_connections[room_name_to_room_index(room_name)];
    int connections_number = room_connections_sizes[room_name_to_room_index(room_name)];

    int number = 0;
    for (number = 0; number < connections_number; number++) {
        const char *name = connections[number];
        fprintf(f, room_connection_format, number, name);
    }
    fprintf(f, room_file_format_footer, room_types[room_type]);
}

void set_start_end_rooms() {
    while (start_room == end_room) {
        start_room = RANDRANGE(0, NUMBER_OF_ROOMS);
        end_room = RANDRANGE(0, NUMBER_OF_ROOMS);
    }
}

void build_rooms() {
    assert(start_room != end_room);
    int i = 0;
    for (i = 0; i < NUMBER_OF_ROOMS; i++) {
        sprintf(buf, "%s/room%d.adventure.txt", dir_name, (i + 1));
        FILE *f = fopen(buf, "w");
        assert(f);
        enum RoomType room_type = MID_ROOM;
        if (i == start_room)
            room_type = START_ROOM;
        else if (i == end_room)
            room_type = END_ROOM;
        build_a_room(f, room_names[i], room_type);
        fclose(f);
    }
}

// This resets the game data so it can be read back in.
void reset() {
    start_room = 0;
    end_room = 0;
    int i;
    for (i = 0; i < NUMBER_OF_ROOMS; i++)
        room_connections_sizes[i] = 0;
}

void read_room_file(int room_id) {
    int res = 0;
    char room_type[30];
    char room_name[30];
    int connection_number = -1;
    char connection_name[30];
    int this_room_index = -1;
    int other_room_index;
    sprintf(buf, "%s/room%d.adventure.txt", dir_name, (room_id + 1));
    FILE *f = fopen(buf, "r");
    while (fgets(buf, BUF_SIZE, f)) {
        sscanf(buf, room_file_format_header, room_name);
        res = sscanf(buf, room_connection_format, &connection_number, connection_name);
        if (res) {
            this_room_index = room_name_to_room_index(room_name);
            other_room_index = room_name_to_room_index(connection_name);
            room_connections[this_room_index][room_connections_sizes[this_room_index]++] = room_names[other_room_index];
        }
        sscanf(buf, room_file_format_footer, room_type);
    }
    assert(this_room_index != -1);
    if (strcmp(room_type, room_types[START_ROOM]) == 0)
        start_room = this_room_index;
    if (strcmp(room_type, room_types[END_ROOM]) == 0)
        end_room = this_room_index;
}

void read_room_files() {
    int i;
    for (i = 0; i < NUMBER_OF_ROOMS; i++)
        read_room_file(i);
}

void enter_room(const char *room_name) {
    printf(prompt_header, room_name);
    int number;
    int room_index = room_name_to_room_index(room_name);
    int connections_number = room_connections_sizes[room_index];
    const char **const connections = room_connections[room_index];

    for (number = 0; number < connections_number; number++) {
        const char *name = connections[number];
        printf("%s", name);
        if (number != connections_number - 1)
            printf(", ");
    }
    printf(prompt_footer);
    fgets(buf, BUF_SIZE, stdin);
    strip(buf);
    int input_room_index = room_name_to_room_index(buf);
    int in_room_index = room_index != -1;
    if (in_room_index && in_room_connections(buf, room_index)) {
        steps++;
        sprintf(buf, "%s", room_path_buffer);
        sprintf(room_path_buffer, "%s%s\n", buf, room_names[input_room_index]);
        if (input_room_index == end_room) {
            printf(winning_message, steps, room_path_buffer);
            return;
        } else {
            enter_room(room_names[input_room_index]);
            return;
        }
    } else {
        printf(error_msg);
        enter_room(room_name);
        return;
    }
}


int main() {
    // Setup
    // ----------
    srand((unsigned int) time(NULL));
    sprintf(dir_name, dir_name_format, getpid());
    assert(mkdir(dir_name, 0777) == 0);

    // Tests
    // ----------
    // Test: room_name_to_room_index
    assert(room_name_to_room_index(room_names[0]) == 0);
    assert(room_name_to_room_index(room_names[1]) == 1);
    assert(room_name_to_room_index("blah") == -1);
    // Test RANDRANGE
    {
        int i;
        for (i = 0; i < 100; i++)
            assert(RANDRANGE(3, 5) >= 3 && RANDRANGE(3, 5) <= 5);
    }
    // Setup:Randomize rooms
    shuffle(room_names, NUMBER_OF_ROOMS);
    // Setup:Build rooms
    build_room_connections();
    // Test:Build Room 0 should have a connection
    assert(room_connections[0][0]);

    // Main Procedure
    set_start_end_rooms();
    build_rooms();
    reset();
    read_room_files();
    enter_room(room_names[start_room]);

    return 0;
}
