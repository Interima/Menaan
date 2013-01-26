function languageDefaulter(id)
{
    var count = languageChanger.children[0].children.length;
    for (var i=0; i<count; i++) languageChanger.children[0].children[i].visible=false;
    languageChanger.children[0].children[id].visible=true;
    currentLanguageItem=id;
}

function multThreadDefaulter(id)
{
    var count = multiThreadChanger.children[0].children.length;
    for (var i=0; i<count; i++) multiThreadChanger.children[0].children[i].visible=false;
    multiThreadChanger.children[0].children[id].visible=true;
    currentMultiThreadItem=id;
}


function finishDeleteDefaulter(id)
{
    var count = finishDeleteChanger.children[0].children.length;
    for (var i=0; i<count; i++) finishDeleteChanger.children[0].children[i].visible=false;
    finishDeleteChanger.children[0].children[id].visible=true;
    currentFinishDeleteItem=id;
}


function extDefaulter(id)
{
    var count = extChanger.children[0].children.length;
    for (var i=0; i<count; i++) extChanger.children[0].children[i].visible=false;
    extChanger.children[0].children[id].visible=true;
    currentExtItem=id;
}

function rewriteDefaulter(id)
{
    var count = rewriteChanger.children[0].children.length;
    for (var i=0; i<count; i++) rewriteChanger.children[0].children[i].visible=false;
    rewriteChanger.children[0].children[id].visible=true;
    currentRewriteItem=id;
}

function configDefaulter(ld,mtd,afd,ed,rd)
{
    languageDefaulter(ld);
    multThreadDefaulter(mtd)
    finishDeleteDefaulter(afd);
    extDefaulter(ed);
    rewriteDefaulter(rd);
}


function languageSwitcher(id)
{
    languageChanger.children[0].children[id].visible=false;
    if (++id == languageChanger.children[0].children.length) id = 0;
    languageChanger.children[0].children[id].visible=true;
    currentLanguageItem=id;
}

function multiThreadSwitcher(id)
{
    multiThreadChanger.children[0].children[id].visible=false;
    if (++id == multiThreadChanger.children[0].children.length) id = 0;
    multiThreadChanger.children[0].children[id].visible=true;
    currentMultiThreadItem=id;
}

function finishDeleteSwitcher(id)
{
    finishDeleteChanger.children[0].children[id].visible=false;
    if (++id == finishDeleteChanger.children[0].children.length) id = 0;
    finishDeleteChanger.children[0].children[id].visible=true;
    currentFinishDeleteItem=id;
}


function extSwitcher(id)
{
    extChanger.children[0].children[id].visible=false;
    if (++id == extChanger.children[0].children.length) id = 0;
    extChanger.children[0].children[id].visible=true;
    currentExtItem=id;
}

function rewriteSwitcher(id)
{
    rewriteChanger.children[0].children[id].visible=false;
    if (++id == rewriteChanger.children[0].children.length) id = 0;
    rewriteChanger.children[0].children[id].visible=true;
    currentRewriteItem=id;
}

function saveConfig()
{
    menaan.configDataSave(currentLanguageItem,
                          currentMultiThreadItem,
                          currentFinishDeleteItem,
                          currentExtItem,
                          currentRewriteItem);

    var comp = Qt.createComponent("Message.qml");
    var obj = comp.createObject(configTab);
    obj.titleText = qsTr("Mena'an");
    obj.dataText = qsTr("Config has been saved.\nRestart application to apply changes.\n\nClick to close.");
}

function resetConfig()
{
    menaan.configDataRecovery();

    var comp = Qt.createComponent("Message.qml");
    var obj = comp.createObject(configTab);
    obj.titleText = qsTr("Mena'an");
    obj.dataText = qsTr("Config has been restored.\nRestart application.\n\nClick to close.");
}

function importConfig()
{
    var comp = Qt.createComponent("Message.qml");
    var obj = comp.createObject(configTab);
    obj.titleText = qsTr("Mena'an");
    obj.dataText = qsTr("Sorry, it's not working.\nComing soon.\n\nClick to close.");

    console.log("Coming soon");
}

function exportConfig()
{
    var comp = Qt.createComponent("Message.qml");
    var obj = comp.createObject(configTab);
    obj.titleText = qsTr("Mena'an");
    obj.dataText = qsTr("Sorry, it's not working.\nComing soon.\n\nClick to close.");

    console.log("Coming soon");
}
