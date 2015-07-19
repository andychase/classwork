#include <stdio.h>
#include <assert.h>

#include <time.h>
#include <stdlib.h>


#define RANDRANGE(a, b)           (rand() % (b-a)) + a

// Configuration
const char *dir_name = "chasean.rooms.%d";
//
const char *room_file_format_header = "ROOM NAME: %s\n";
const char *room_file_format_footer = "ROOM TYPE: %s\n";
//
const char *room_connection_format = "CONNECTION %d: %s\n";
//
const char *room_types[] = {"MID_ROOM", "START_ROOM", "END_ROOM"};

//
const char *room_names[] = {"PLUGH", "PLOVER", "twisty", "Zork", "Crowther", "Dungeon"};

#define NUMBER_OF_ROOMS 7
//
const char *room_connections[NUMBER_OF_ROOMS][NUMBER_OF_ROOMS];
int room_connections_sizes[NUMBER_OF_ROOMS];
//
//
#define CONNECTIONS_MIN 3
#define CONNECTIONS_MAX 6
//
const char *error_msg = "HUH? I DON'T UNDERSTAND THAT ROOM. TRY AGAIN.";
//
const char *prompt_header = "CURRENT LOCATION: %s\nPOSSIBLE CONNECTIONS: ";
const char *prompt_footer = ".\nWHERE TO? > ";
//
const char *winning_message = "YOU HAVE FOUND THE END ROOM. CONGRATULATIONS!\n"
    "YOU TOOK %d STEPS. YOUR PATH TO VICTORY WAS:\n"
    "%s";
//
int steps = 0;
//
char room_path_buffer[10000];

//
//
int room_name_to_room_index(const char *key) {
    int i;
    for (i = 0; i < NUMBER_OF_ROOMS; i++) {
        if (key == room_names[i])
            return i;
        else
            i += 1;
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
            const char * room = rooms_left[i];
            if (!in_room_connections(room, this_room_index)) {
                int other_room_index = room_name_to_room_index(room);
                room_connections[this_room_index][room_connections_sizes[this_room_index]++] = room;
                if (!in_room_connections(this_room, other_room_index))
                    room_connections[other_room_index][room_connections_sizes[other_room_index]++] = this_room;
            }
        }
    }
}
//
// def build_a_room(f, the_dir_name, room_connections, room_name, start=False, end=False):
//     room_type = room_types[0]
//     if start:
//         room_type = room_types[1]
//     elif end:
//         room_type = room_types[2]
//
//     f.write(room_file_format_header % room_name)
//     connections = room_connections[room_name_to_room_index(room_names, room_name)]
//     for number, name in enumerate(connections):
//         f.write(room_connection_format % (number, name))
//     f.write(room_file_format_footer % room_type)
//
//     if start:
//         f2 = open(the_dir_name + "/START.adventure.txt", 'w')
//         f2.write(prompt_header % room_name)
//         for number, name in enumerate(connections):
//             f2.write(name)
//             if number != len(connections) - 1:
//                 f2.write(", ")
//         f2.write(prompt_footer)
//
//     f2 = open(the_dir_name + "/%s.adventure.txt" % room_name, 'w')
//     f2.write(prompt_header % room_name)
//     for number, name in enumerate(connections):
//         f2.write(name)
//         if number != len(connections) - 1:
//             f2.write(", ")
//     f2.write(prompt_footer)
//
//
// def build_rooms(_room_connections):
//     the_dir_name = dir_name % os.getpid()
//     if not os.path.isdir(the_dir_name):
//         os.mkdir(the_dir_name)
//     for i in range(0, number_of_rooms):
//         f = open(the_dir_name + "/room%d.adventure.txt" % (i + 1), 'w')
//         build_a_room(f, the_dir_name, _room_connections, room_names[i], start=(i == 0), end=(i == 1))
//         f.close()
//
//
// def enter_room(room_name):
//     global steps
//     the_dir_name = dir_name % os.getpid()
//     f = open(the_dir_name + "/%s.adventure.txt" % room_name)
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
// def main():
//     global steps
//     random.shuffle(room_names)
//     rand_gen = lambda: random.randint(connections_min, connections_max)
//     _room_connections = build_room_connections(room_names, room_connections, rand_gen)
//     build_rooms(_room_connections)
//     buf = enter_room("START")
//     print(winning_message % (steps, buf))
//     # #include <stdlib.h>
//     # "Cheating" a bit here since I don't think cleanup
//     # was a primary part of the assignment
//
//     # system("rm -fr %s" % the_dir_name)
//

int main() {
    // Setup
    // ----------
    srand((unsigned int) time(NULL));

    // Tests
    // ----------
    // Test: room_name_to_room_index
    assert(room_name_to_room_index(room_names[0]) == 0);
    assert(room_name_to_room_index("blah") == -1);
    // Test RANDRANGE
    {
        int i;
        for (i = 0; i < 100; i++)
            assert(RANDRANGE(3, 5) >= 3 && RANDRANGE(3, 5) <= 5);
    }
    build_room_connections();
    // Room 0 should have a connection
    assert(room_connections[0][0]);

    puts("test");

    return 0;
}