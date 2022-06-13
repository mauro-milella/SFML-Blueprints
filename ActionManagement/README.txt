# Action Manager Blueprint

**What is implemented**
Action: basic class containing an event and it's trigger-type (es. ButtonPressed)

ActionMap: implements mapping between a certain key and an action. This is a template class because "key" 
could be something different than an integer code (es. a string for events related to text)

ActionTarget: keys are binded to specific callbacks (void function) and are stored in 2 lists: _eventsRealTime and _eventsPoll.
In processEvents(), for each <key, callback> in _eventsRealTime:
1) action binded to "key" is retrieved from an ActionMap object 
2) having an action, now we can check whether it's event is happening or not
3) if so, we can finally invoke the callback
Unbinding is implemented too.

A Player class skeleton is implemented too.
Player::setDefaultsInput() static method is needed to initialize the ActionMap (which is shared with ActionTarget) with <key, action> pairs.
The initialization of Player's involve filling an ActionTarget object with <key, callback> bindings:
thus setDefaultsInput must be called before (in fact ActionTarget needs a complete ActionMap object to operate).

E.g. The first instruction in main could be Player::setDefaultsInput(), before starting the game.

This blueprint purpose is to generalize input management and make it flexible to the player.
Moreover, when anything calls Player.processEvents() events management is forwarded to ActionTarget.