# Evoland GB

![](./evoland-gb-logo.png)

Evoland.gb is a fan-made port of the Evoland game, on the Nintendo GameBoy console. This project is still in a work-in-progress state, but it is in a sufficiently advanced state to be shown.

For those who do not know Evoland, It is the first game of Shiro Games studio. It takes the form of an action RPB that relates the history of the video game through its technological evolutions and its gameplay. I will not tell you more about it, but if the concept interests you, you will find many let's plays on Youtube.

For more informations,

* visit the project's website: https://evogb.flozz.org/
* or read this article on my blog (French): https://blog.flozz.fr/2019/04/21/evoland-sur-gameboy/

## Building Evoland.gb

### Installing Build Dependencies

To build Rvoland.gb, the SDCC  compiler is required with its libraries and gbz80 support. On Ubuntu / Debian, this can be done with the following command:

    sudo apt install sdcc sdcc-libraries

### Cloning this repository

Then you have to clone this repository:

    git clone git@github.com:flozz/evoland.gb.git

Next go to the project folder

    cd evoland.gb

And download submodules

    git submodule init
    git submodule update

### Building the ROMs

Finally, just build the ROMs with the following command:

    make

If everything is OK, the following files are generated:

* `evoland_en.gb`: English ROM of Evoland.gb
* `evoland_fr.gb`: French ROM of Evoland.gb

### Updating assets

If you change assets (map or tilesets in `gassets/` folder), you have to rebuild the assets:

    make gassets

**NOTE:** You will have to install [img2gb](https://github.com/flozz/img2gb) to build the assets.


## Changelog

* **0.3.0** First public release

