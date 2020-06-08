# Description

This repo is used to demonstrate how I use Unreal Engine built-in networking stuff to implmenet the client-server model.

Player is able to:

1. Create session
2. Search session
3. Join session
4. Leave session
5. Destroy session

# Demo Videos

1. [Create and Search Session](https://youtu.be/oxaVHqnWLnQ)
2. [Join Session with Replication](https://youtu.be/PuTgP1X8BDg)
3. [RPC Function Demo - Firing](https://youtu.be/G_VfS_E60vU)

# How to test Online Stuff

Because of PIE cannot connect LAN session within the editor, so that every time I need a packaged version to test the online multiplay stuff.
Before you start to debug and run the game, please do the following steps:

1. Modify the `RunGame.bat` change the `UE4Editor.exe` and `.uproject` to the correct path
2. Run twice
3. Use one of them to create session, and the other one search session and click the server to join the session

PS: If you can't find any session in the list, please check your network settings.

# References

1. [UE4-Multiplayer-Example](https://github.com/minimpoun/UE4-Multiplayer-Example)
2. [How to use SocketIO to connect Unreal Engine, website and other devices](https://medium.com/@slonorib/how-to-connect-unreal-engine-4-to-local-server-via-sockets-9d73fd180f0b)
3. [Unreal Engine Networking Get Started Document](https://docs.unrealengine.com/en-US/Gameplay/Networking/index.html)
4. [How to override game session in game mode](https://forums.unrealengine.com/development-discussion/c-gameplay-programming/6059-help-how-do-i-create-initialized-game-session)
5. [Lecture 05 - Multiplayer and Network Communication in Unreal Engine](http://edirlei.3dgb.com.br/aulas/dp/DP_Lecture_05_Multiplayer_Unreal_Engine.pdf)
6. [[WIKI] [Finished] C++ Session Create/Find/Join/Destroy](https://forums.unrealengine.com/community/community-content-tools-and-tutorials/49645-wiki-finished-c-session-create-find-join-destroy)
7. [Legacy/How To Use Sessions In C++ - ue4community](https://www.ue4community.wiki/Legacy/How_To_Use_Sessions_In_C%2B%2B)
8. [How To Use Sessions In C++](https://unreal.gg-labs.com/wiki-archives/networking/how-to-use-sessions-in-c++)
9. [Use RPC function with Unreal Engine](https://docs.unrealengine.com/en-US/Gameplay/Networking/Actors/RPCs/index.html)