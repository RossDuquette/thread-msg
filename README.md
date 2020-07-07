# thread-msg

Library that can be used to create a module framework.
See `thread-msg-example` for an example use case. It may be
useful to use this as a template for other projects.

To create a custom module, inherit the `Module` class.
Each module is spawned in its own pthread.

To create a custom topic, inherit the `Msg` class.

Messages are sent using a publish/subscribe concept.
Every module will have access to a `Messenger` object
to be used to communicate over a specific topic. Any number
of modules can publish/subscribe to a specific topic.

`FreqSleeper` and `FreqSleeperRT` are classes that can be
used in your module to introduce breaks into your module's loop.
Modules that do not block are suggested to use one of these
classes in their main loop.
Modules that block listening to a topic should not sleep.

It is possible for one Module to spawn multiple child modules.
To do this, follow a similar design pattern in `.main()` as used
in `thread-msg-example/main.cpp`. That is:
* Create child module objects.
* Call `.start()` on each object.
* Delete the child modules in the destructor.
