# FUCKCAPS

### This program is simple:

- Press `Caps Lock` to enter action mode.
- In action mode, you can use Vim motions with the H, J, K, and L keys (essentially remapping the arrow keys).
- You can record shortcuts (macros) by pressing the `ESC` button. For example, if you want to set `CONTROL+C` for the `A` you do this: `A,CONTROL+C`(or press your desired combination). Press the `ESC` again to exit record mode.
- You can visually configure anything you want in the terminal app (still in development).

If you want to hear the story behind the inspiration for this project, check out `FUCKCAPS.md`.

### TODO Ideas that will make the FuckCaps better:

- [x] Integrate a .yaml config file.
- [x] Integrate shortcuts and macros.
  - [ ] Make it so that when a command is triggered, it turns off Caps Lock.
- [ ] Create a better terminal menu using FTXUI.
  - [ ] Enable FTXUI to interact with the key_config.yaml for parsing and emitting.
- [ ] Display the status of FUCKCAPS on top of all active windows.
- [ ] Exclude certain applications from having any impact when action mode is enabled.
- [ ] Launch it on Homebrew (because who doesn’t love a good formula?).

### Compilation Instructions

Want to make this work with plugins like coc.nvim or YouCompleteMe (YCM) for improved code navigation and completion? You’ll need to generate a compile_commands.json file. Here’s how to do it:

```bash
$ mkdir build && cd build
$ cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
$ make
$ ./fuckcaps
```

Then link or copy this file to the root of your project:

```bash
$ cd ..
$ ln -s build/compile_commands.json
```

### Contributing

Dear contributer, this is shitty code. I’m still learning how to code and as of now, it’s not the most performance-efficient or bug-free masterpiece. I would greatly appreciate your help in improving both the code and my understanding. Your pull requests (PRs) are welcome—bring on the constructive criticism!

### Donations

If you enjoy this project and want to support its continued development (or just want to buy me a coffee), consider donating! Here are a few ways you can do that:

- Patreon: [Support me on Patreon](https://patreon.com/SepantaMirhajian)

- Buy Me a Coffee:

For the fellows from Iran ❤️:

- Coffee Bede:
  [![Support me on CoffeeBede](https://coffeebede.ir/DashboardTemplateV2/app-assets/images/banner/default-yellow.svg)](https://www.coffeebede.com/abolafzlmirhajian)
