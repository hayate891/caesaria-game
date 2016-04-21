game.ui.dialogs.citydonation = {}

game.ui.dialogs.citydonation.show = function() {
  var ibox = g_ui.addSimpleWindow(0, 0, 510, 160);

  ibox.title = _u("send_money_to_city");

lbBlack#Label : {
  geometry : [ 50, 50, 465, 110 ]
  bgtype : "blackFrame"
  font : "FONT_3"
  text.align : [ "center", "center" ]

  btn0#PushButton : {
    geometry : [ 15, 10, 80, 30 ]
    font : "FONT_1"
    text : "0"
    pushbutton : false
    id : 3840  /*0x0F00*/
    tooltip : "##set_amount_to_donate##"
    bgtype : "blackBorderUp"
  }

  btn500#PushButton : {
    geometry : [ 95, 10, 160, 30 ]
    font : "FONT_1"
    text : "500"
    pushbutton : false
    id : 3841  /*0x0F01*/
    tooltip : "##set_amount_to_donate##"
    bgtype : "blackBorderUp"
  }

  btn2000#PushButton : {
    geometry : [ 175, 10, 240, 30 ]
    font : "FONT_1"
    text : "2000"
    pushbutton : false
    id : 3844  /*0x0F03*/
    tooltip : "##set_amount_to_donate##"
    bgtype : "blackBorderUp"
  }

  btnAll#PushButton : {
    geometry : [ 255, 10, 380, 30 ]
    font : "FONT_1"
    pushbutton : false
    text : "##send_all##"
    id : 4095  /*0xfff*/
    tooltip : "##set_amount_to_donate##"
    bgtype : "blackBorderUp"
  }

  lbDonation#Label : {
    geometry : [ 25, 32, 250, 56 ]
    text : "##donation_is##"
    textAlign : [ "center", "center" ]
    font : "FONT_2"
  }

  btnDecreaseDonation#TexturedButton : {
    id : 4097 /*0x1001*/
    geometry : [ 255, 32, 279, 56 ]
    normal : [ "paneling", 601 ]
    hovered : [ "paneling", 602 ]
    pressed : [ "paneling", 603 ]
    disabled : [ "paneling", 301 ]
  }

  btnIncreaseDonation#TexturedButton : {
    id : 4098 /*0x1002*/
    geometry : [ 280, 32, 304, 56 ]
    normal : [ "paneling", 605 ]
    hovered : [ "paneling", 606 ]
    pressed : [ "paneling", 607 ]
    disabled : [ "paneling", 305 ]
  }
}

btnSend#PushButton : {
  geometry : [ 80, "ph-35", 240, "ph-15" ]
  font : "FONT_2"
  text : "##give_money##"
  tooltip : "##give_money_tip##"
  bgtype : "whiteBorderUp"
}

btnCancel#PushButton : {
  geometry : [ 270, "ph-35", 430, "ph-15" ]
  font : "FONT_2"
  text : "##cancel##"
  tooltip : "##donationwnd_exit_tip##"
  bgtype : "whiteBorderUp"
}
}
