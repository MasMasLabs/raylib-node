const raylib = require('./dist/node_raylib');

raylib.initWindow(1200, 960, 'First raylib integration');
raylib.setTargetFPS(60);

while(!raylib.windowShouldClose()) {
    raylib.beginDrawing();
    raylib.clearBackground({
        r: 40,
        g: 30,
        b: 20,
        a: 200,
    });
    raylib.drawText({
        text: 'raylib is awesome!',
        posX: 400,
        posY: 200,
        fontSize: 30,
        color: {
            r: 240,
            g: 190,
            b: 0,
            a: 250,
        }
    });
    raylib.endDrawing();
}

raylib.closeWindow();