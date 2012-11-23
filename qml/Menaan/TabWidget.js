function tabSwitch(tabNum)
{
    var count = containerArea.children.length;
    for (var i=0; i<count; i++)
    {
        if ((containerArea.children[i].state === "active")&&
                (i!==tabNum-1)) containerArea.children[i].state = "inactive";

        if ((containerArea.children[i].state === "inactive")&&
                (i===tabNum-1)) containerArea.children[i].state = "active";
    }



}

