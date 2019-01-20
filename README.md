# gmsv_floodgate

Original code https://github.com/cannon/gmsv_floodgate

Mitigates many server lag exploits based on spamming some kind of console message.

To use it, require the module and then call the ConsoleFloodgate(x) function every so often to allow x more messages to print to the console.

Compiled DLL and lua for your server is in release. For the version I compiled, you'll need vcruntime140.dll in your server folder (alongside srcds.exe)

Lots of code used from gm_spew: https://github.com/LennyPenny/gm_spew (based on my tests, using a hook with gm_spew doesn't prevent lag exploits, but this module does)
