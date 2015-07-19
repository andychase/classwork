/*
 Andy Chase
 chasean


I used the protoype-first method for building this assignment for the following reasons:

* I've never used the prototype-first method and I wanted to try it
* I have more practice in python than in c so I wanted to think through the problem in a familiar language
* The spec was clear and static
* This assignment had basically two parts:
- Figuring out the solution
- Figuring out how to actually write the solution in c
 (so it makes sense to figure out the solution in a different language)

My experience with the prototype-first solution:

 Overall it felt longer, but I liked it because I was able to flesh out the solution
 and get a really strong feeling for its correctness before I dove in and did the implementation.
 (Honestly it probably overall would have taken longer to start in c first, but it did FEEL longer)

 It gave me a strong structure to start with which I liked and allowed me to just bypass any "writers block" or
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


#define RANDRANGE(a, b)           (rand() % (b-a)) + a

// Configuration
#define dir_name_format "chasean.rooms.%d"
//

//
enum RoomType {
    MID_ROOM = 0, START_ROOM, END_ROOM
};
const char *room_types[] = {"MID_ROOM", "START_ROOM", "END_ROOM"};

//
const char *room_names[] = {"PLUGH", "PLOVER", "twisty", "Zork", "Crowther", "Dungeon", "YA"};

#define NUMBER_OF_ROOMS 7
//
const char *room_connections[NUMBER_OF_ROOMS][NUMBER_OF_ROOMS];
int room_connections_sizes[NUMBER_OF_ROOMS];
//
//
#define CONNECTIONS_MIN 3
#define CONNECTIONS_MAX 6
// Configuration: Strings
#define room_file_format_header "ROOM NAME: %s\n"
#define room_file_format_footer "ROOM TYPE: %s\n"
//
#define room_connection_format "CONNECTION %d: %s\n"

#define error_msg "HUH? I DON'T UNDERSTAND THAT ROOM. TRY AGAIN."
//
#define prompt_header "CURRENT LOCATION: %s\nPOSSIBLE CONNECTIONS: "
#define prompt_footer ".\nWHERE TO? > "
//
#define winning_message "YOU HAVE FOUND THE END ROOM. CONGRATULATIONS!\n"\
"YOU TOOK %d STEPS. YOUR PATH TO VICTORY WAS:\n"\
"%s"

//
int steps = 0;
//
char room_path_buffer[10000];
char buf[100000];
char dir_name[36];

// Helper Shuffle Fucntion
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

int room_name_to_room_index(const char *key) {
    int i;
    for (i = 0; i < NUMBER_OF_ROOMS; i++) {
        if (key == room_names[i])
            return i;
    }
    return -1;
}

int in_room_connections(const char *test_room, int room_index) {
    int i;
    for (i = 0; i < room_connections_sizes[room_index]; i++)
        if (room_connections[room_index][i] == test_room)
            return 1;
    return 0;
}

//
//
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

void build_a_room(FILE *f, const char *the_dir_name, const char *room_name, enum RoomType room_type) {
    fprintf(f, room_file_format_header, room_name);
    const char **const connections = room_connections[room_name_to_room_index(room_name)];
    int connections_number = room_connections_sizes[room_name_to_room_index(room_name)];

    int number = 0;
    for (number = 0; number < connections_number; number++) {
        const char *name = connections[number];
        fprintf(f, room_connection_format, number, name);
    }
    fprintf(f, room_file_format_footer, room_types[room_type]);

    if (room_type == START_ROOM) {
        sprintf(buf, "%s/START.adventure.txt", the_dir_name);
        FILE *f2 = fopen(buf, "w");

        fprintf(f2, prompt_header, room_name);
        for (number = 0; number < connections_number; number++) {
            const char *name = connections[number];
            fprintf(f2, "%s", name);
            if (number != connections_number - 1)
                fprintf(f2, ", ");
        }
        fprintf(f2, prompt_footer);
        fclose(f2);
    }
    sprintf(buf, "%s/%s.adventure.txt", the_dir_name, room_name);
    FILE *f2 = fopen(buf, "w");
    fprintf(f2, prompt_header, room_name);
    for (number = 0; number < connections_number; number++) {
        const char *name = connections[number];
        fprintf(f2, "%s", name);
        if (number != connections_number - 1)
            fprintf(f2, ", ");
    }
    fprintf(f2, prompt_footer);
}

void build_rooms() {
    int start_room = 0;
    int end_room = 0;
    while (start_room == end_room) {
        start_room = RANDRANGE(0, NUMBER_OF_ROOMS);
        end_room = RANDRANGE(0, NUMBER_OF_ROOMS);
    }

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
        build_a_room(f, dir_name, room_names[i], room_type);
        fclose(f);
    }
}
// def enter_room(room_name):
//     global steps
//     dir_name = dir_name_format % os.getpid()
//     f = open(dir_name + "/%s.adventure.txt" % room_name)
//     buf = f.read()
//     print(buf)
//     f.close()
//     new_path = ""
//     path = ""
//     while not new_path:
//         path = input()
//         if path in buf and path in room_names:
//             new_path = path
//         else:
//             print(error_msg)
//             print(buf)
//     steps += 1
//     if path == room_names[1]:
//         return path
//     else:
//         return path + "\n" + enter_room(path)
//
//

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

    build_rooms();
    //enter_room("START");

    // Cleanup temporary ui files
    int i = 0;
    for (i = 0; i < NUMBER_OF_ROOMS; i++) {
        sprintf(buf, "%s/%s.adventure.txt", dir_name, room_names[i]);
        unlink(buf);
    }
    sprintf(buf, "%s/START.adventure.txt", dir_name);
    unlink(buf);

    return 0;
}