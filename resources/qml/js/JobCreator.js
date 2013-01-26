//! args that will be pushed to menaan
var args = new Array(6);

// send args to menaan
function command(id,type)
{
    if (verificator(type) == -1) return;
    menaan.createJob(args[0],args[1],args[2],args[3],args[4],args[5]);
}

// validate input data
function verificator(type)
{
    // validate input path
    if ((inputPath.realText.length==0)||
        (inputPath.realText === inputPath.defaultText))
    {
        errorMsg(qsTr("Invalid input path."));
        console.log("Catastrophic error! Error input path");
        return -1;
    }

    // validate output path
    if ((outputPath.realText.length==0)||
        (outputPath.realText === outputPath.defaultText))
    {
        errorMsg(qsTr("Invalid output path."));
        console.log("Catastrophic error! Error output path");
        return -1;
    }

    // validate key
    if ((key.realText.length==0)||
        (key.realText === key.defaultText))
    {
        errorMsg(qsTr("Invalid key."));
        console.log("Catastrophic error! Error in key");
        return -1;
    }

    args[0] = inputPath.realText;
    args[1] = outputPath.realText;
    args[2] = key.realText;

    // special parameters can be empty or default
    if ((special.realText.length==0)||
        (special.realText === special.defaultText))
        args[3] = "";
    else
        args[3] = special.realText;

    // Amazing bug in Qt
    // Cannot send enum as parameter
    args[4] = Number(type);

    args[5] = pluginIndex;

    return 0;
}

function setTextFor(item,str)
{
    item.setText(str);
}

function answerArrived(whois,str)
{
    if (whois=="input") setTextFor(inputPath,str);
    if (whois=="output") setTextFor(outputPath,str);
}

// show error message
function errorMsg(str)
{
    var comp = Qt.createComponent("Message.qml");
    var obj = comp.createObject(form);
    obj.titleText = qsTr("Mena'an");
    obj.dataText = str+"\n\nClick to close.";
}
