# Errantry

Errantry is a turned-based RPG with text graphics, inspired mainly by 90s-era Squaresoft RPGs. 

I originally built the game in 2000 for a school project while learning C++. In January 2016 I decided to revisit the project as a way to get reacquainted with C++, learn more about git since I use Mercurial day-to-day, and add in features I had intended but was not able to get complete in time for submitting the project.

## Contributing

Currently I am not using an open source software license at this time, so the project remains under Copyright except where in conflict with the GitHub Terms of Use (i.e. viewing and forking it).

My intention for putting the project on GitHub is primarily to have a central off-site host for cloning the project to different machines on which I might develop it.

If there happens to be serious interest in contributing (e.g. I start seeing pull requests), I may reconsider licensing the source under the MIT license or GPL in the future.

## Building and Running

### Mac/Linux

Pre-requisites:
- Assumes g++ is installed.

From the root folder of errantry:

```
cd Debug
make all
./errantry 
```

The project can also be imported into Eclipse CDT and built from within. 

### Windows

Planning on this soon.

## Installing 

### (Mac/Linux)

Beforehand, make sure `/usr/local/games` is in your `PATH`.

Assuming you are in the repository directory:
```
mkdir /usr/local/share/errantry
cp dat /usr/local/share/errantry
mkdir /usr/local/share/errantry/bin
cp Debug/errantry /usr/local/share/errantry/bin
cp scripts/launch_errantry.sh /usr/local/share/errantry/bin
chmod +x launch_errantry.sh errantry
ln -s /usr/local/share/errantry/bin/launch_errantry.sh /usr/local/games/errantry
```

The reason for symlinking to `launch_errantry.sh` instead of directly to the errantry binary is because currently errantry references its dat folder via a hardcoded relative path (`../dat`).  If the symlink launches errantry directly, this will cause errantry to look for its dat folder in the parent of the symlink, rather than the actual parent of the binary itself.

Hopefully this will be improved in a later version. =)

### Windows

Planning on this soon.