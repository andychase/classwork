import sys
import os
import random

# Config

dir_name = "chasean.rooms.%d"

room_file_format_header = """ROOM NAME: %s
"""
room_file_format_footer = """ROOM TYPE: %s
"""

room_connection_format = \
    """CONNECTION %d: %s
"""

room_types = ["MID_ROOM", "START_ROOM", "END_ROOM"]

room_names = "XYZZY PLUGH PLOVER twisty Zork Crowther Dungeon".split()

room_names2 = room_names[:]

number_of_rooms = 7

connections_min = 3

connections_max = 6

error_msg = """
HUH? I DON'T UNDERSTAND THAT ROOM. TRY AGAIN.
"""

prompt_header = """CURRENT LOCATION: %s
POSSIBLE CONNECTIONS: """
prompt_footer = """.
WHERE TO? > """

winning_message = """YOU HAVE FOUND THE END ROOM. CONGRATULATIONS!
YOU TOOK %d STEPS. YOUR PATH TO VICTORY WAS:
%s
"""

steps = 0


def build_a_room(f, the_dir_name, room_name, start=False, end=False):
    number_of_connections = random.randint(connections_min, connections_max)
    random.shuffle(room_names)
    room_type = room_types[0]
    if start:
        room_type = room_types[1]
    elif end:
        room_type = room_types[2]

    f.write(room_file_format_header % room_name)
    connections = room_names[:number_of_connections]
    for number, name in enumerate(connections):
        f.write(room_connection_format % (number, name))
    f.write(room_file_format_footer % room_type)

    if start:
        f2 = open(the_dir_name + "/START.adventure.txt", 'w')
        f2.write(prompt_header % room_name)
        for number, name in enumerate(connections):
            f2.write(name)
            if number != len(connections)-1:
                f2.write(", ")
        f2.write(prompt_footer)

    f2 = open(the_dir_name + "/%s.adventure.txt" % room_name, 'w')
    f2.write(prompt_header % room_name)
    for number, name in enumerate(connections):
        f2.write(name)
        if number != len(connections)-1:
            f2.write(", ")
    f2.write(prompt_footer)


def build_rooms():
    the_dir_name = dir_name % os.getpid()
    if not os.path.isdir(the_dir_name):
        os.mkdir(the_dir_name)
    for i in range(0, number_of_rooms):
        f = open(the_dir_name + "/room%d.adventure.txt" % (i + 1), 'w')
        build_a_room(f, the_dir_name, room_names2[i], start=(i == 0), end=(i == 1))
        f.close()


def enter_room(room_name):
    global steps
    the_dir_name = dir_name % os.getpid()
    f = open(the_dir_name + "/%s.adventure.txt" % room_name)
    buf = f.read()
    print(buf)
    f.close()
    new_path = ""
    path = ""
    while not new_path:
        path = input()
        if path in buf and path in room_names:
            new_path = path
        else:
            print(error_msg)
            print(buf)
    steps += 1
    if path == room_names2[1]:
        return path
    else:
        return path + "\n" + enter_room(path)


def main():
    global steps
    random.shuffle(room_names2)
    build_rooms()
    buf = enter_room("START")
    print(winning_message % (steps, buf))
    return 0


if __name__ == "__main__":
    main()
