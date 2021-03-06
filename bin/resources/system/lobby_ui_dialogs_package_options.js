lobby.ui.dialogs.showPackageOptions = function () {
    var wnd = g_ui.addWindow(0, 0, 450, 300);
    wnd.mayMove = false;
    wnd.title = "##package_options##";
    wnd.closeAfterKey({
        escape: true,
        rmb: true
    });
    var needRestartPckg = false;

    var ww = wnd.w;
    var wh = wnd.h;
    var lbResourcesPath = wnd.addLabel(15, 45, ww * 0.3, 24);
    lbResourcesPath.font = "FONT_1";
    lbResourcesPath.text = "Resources: ";

    var edResourcesPath = wnd.addEditbox(ww * 0.3, 45, ww * 0.7 - 15, 24);
    edResourcesPath.font = "FONT_1";
    edResourcesPath.text = engine.getOption("resourcePath");
    edResourcesPath.textOffset = {x: 3,y: 0};
    edResourcesPath.onTextChangeCallback = function (text) {
        engine.setOption("resourcePath", text);
    }

    var lbCaesar3Path = wnd.addLabel(15, 72, ww * 0.3, 24);
    lbCaesar3Path.font = "FONT_1";
    lbCaesar3Path.text = "C3 gfx: ";

    var edCaesar3Path = wnd.addEditbox(ww * 0.3, 72, ww * 0.7 - 15, 24);
    edCaesar3Path.font = "FONT_1";
    edCaesar3Path.textOffset = {x: 3,y: 0};
    edCaesar3Path.text = engine.getOption("c3gfx");

    var lbCaesar3Music = wnd.addLabel(15, 100, ww * 0.3, 24);
    lbCaesar3Music.font = "FONT_1";
    lbCaesar3Music.text = "C3 snd: ";

    var edCaesar3Music = wnd.addEditbox(ww * 0.3, 100, ww * 0.7 - 15, 24);
    edCaesar3Music.font = "FONT_1";
    edCaesar3Music.textOffset = {x: 3,y: 0};
    edCaesar3Music.text = engine.getOption("c3music");
    edCaesar3Music.onTextChangeCallback = function (text) {
        engine.setOption("c3music", text);
    }

    var lbCaesar3Video = wnd.addLabel(15, 127, ww * 0.3, 24);
    lbCaesar3Video.font = "FONT_1";
    lbCaesar3Video.text = "C3 video: ";

    var edCaesar3Video = wnd.addEditbox(ww * 0.3, 127, ww * 0.7 - 15, 24);
    edCaesar3Video.font = "FONT_1";
    edCaesar3Video.textOffset = {x: 3,y: 0};
    edCaesar3Video.text = g_session.c3video
    edCaesar3Video.onTextChangeCallback = function (text) {
        g_session.c3video = text
    }

    var lbScreenshots = wnd.addLabel(15, 154, ww * 0.3, 24);
    lbScreenshots.font = "FONT_1";
    lbScreenshots.text = "Screenshots: ";

    var edScreenshots = wnd.addEditbox(ww * 0.3, 154, ww * 0.7 - 15, 24);
    edScreenshots.font = "FONT_1";
    edScreenshots.textOffset = {x: 3,y: 0};
    edScreenshots.text = g_session.screenshotdir;
    edScreenshots.onTextChangeCallback = function (text) {
        g_session.screenshotdir = text;
    }

    var lbApply = wnd.addLabel(180, wh - 35, ww - 80, 20);
    lbApply.text = "##plname_continue##";
    lbApply.font = "FONT_2";
    lbApply.textAlign = {w: "lowerRight",h: "center"};

    var btnApply = wnd.addTexturedButton(ww - 40, wh - 40, 27, 27);
    btnApply.states = { rc: "paneling", normal: 179, hover: 180, pressed: 181, disabled: 179 };
    btnApply.tooltip = "##pckopt_apply##";
    btnApply.callback = function () {
        if (needRestartPckg)
            g_ui.addInformationDialog("Note", "Please restart game to apply change");

        if (!g_session.screenshotdir.exist())
            g_session.createDir(g_session.screenshotdir.str);

        wnd.deleteLater();
    }

    var lbExitHelp = wnd.addLabel(18, wh - 35, 160, 20);
    lbExitHelp.text = "##press_escape_to_exit##";
    lbExitHelp.font = "FONT_1";

    edCaesar3Path.onTextChangeCallback = function (text) {
        engine.setOption("c3gfx", text);

        if (text.length == 0) {
            engine.setOption("c3music", "");
            engine.setOption("c3video", "");
        } else {
            needRestartPckg = true;
            engine.setOption("c3music", text + "/wavs");
            engine.setOption("c3video", text + "/smk");
        }

        edCaesar3Music.text = engine.getOption("c3music");
        edCaesar3Video.text = engine.getOption("c3video");
    }

    wnd.moveToCenter();
    wnd.mayMove = false;
    wnd.setModal();
}
