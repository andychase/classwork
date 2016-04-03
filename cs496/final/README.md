Andy Chase
CS 496

My Project
----------

Instead of trying to just make something using tools I used for the other projects in this course (Adobe Air), I decided to just accept getting a poorer grade and try and learn native iOS development.

This was my first time writing a native app, and I had to learn Swift/Xcode from scratch for this project.

I watched the [Intro to iOS App Development with Swift](https://www.udacity.com/course/intro-to-ios-app-development-with-swift--ud585) udacity course to guide me, but my project was much different then the one built in the course.

The end result doesn't look like much, but it was a lot of work and I'm glad I did it rather than go an easy route.

I wasn't able to implement a "mobile feature", unfortunately.

Details
-------

The app is a "todo"-list type app. Once users login/register they can add/remove/move their own personal list of strings as well as a global list. These lists are synced to the cloud.

Mobile: Native iOS
Cloud: Flask + Redis

Api Reference
---------

/register
POST with ?username=username&password=password

Registers an account. Returns {'id': '<account id>'} if success, or {'id': ''} on failure (such as account name is already used).

/login
POST with ?username=username&password=password

Registers an account. Returns {'id': '<account id>'} if success, or {'id': ''} on failure.

/get
GET with ?get_user_list="<true or false>"&user=<account id>

Either get the global list with get_user_list=false or get your own personal list with get_user_list=true and user= your account id you get from login

/set
POST with json encoded body

This requires a json post with {
	'get_user_list': '<true or false>'
	'user': <account id, only used when get_user_list=false>
	'data': <string list of todo list items>
}

This endpoint updates the user or global lists.