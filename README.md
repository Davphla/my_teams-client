# My teams

This project consist in a Server / Client creation of a simple protocol based on the software "Teams" by Microsoft.

I was assigned for the Client and use some concept I really like, so here is it.

## How to use it

```bash
./myteams_cli ip port
```

## Features

    /help : show help
    /login [“user_name”] : set the user_name used by client
    /logout : disconnect the client from the server
    /users : get the list of all users that exist on the domain
    /user [“user_uuid”] : get information about a user
    /send [“user_uuid”] [“message_body”] : send a message to a user
    /messages [“user_uuid”] : list all messages exchange with an user
    /subscribe [“team_uuid”] : subscribe to the event of a team and its sub directories (enable reception of all events from a team)
    /subscribed ?[“team_uuid”] : list all subscribed teams or list all users subscribed to a team
    /unsubscribe [“team_uuid”] : unsubscribe from a team
    /use ?[“team_uuid”] ?[“channel_uuid”] ?[“thread_uuid”] : use specify a context team/channel/thread
    /create : based on what is being used create the sub resource (see below)
    /list : based on what is being used list all the sub resources (see below)
    /info : based on what is being used list the current (see below)


## Result :trophy:

|                          Label                        |      Note       |
|:----------------------------------------------------------:|:------------------:|
|           All | 1 / 1 |

