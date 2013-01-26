/// Calculate mitems width
function getMenuItemsWidth()
{
  var width = 0;
  for (var i=0; i<menu.children.length; i++) width+=menu.children[i].width;
  return width;
}

// activate mitem
function activate(id)
{
   id.state = "active";
}

// deactivate mitem
function deactivate(id)
{
   id.state = "inactive";
}

/// click handler
function mitemOnClick(id,num)
{
    if (id===currentItem) return;
    activate(id);
    deactivate(currentItem);
    currentItem=id;
    currentItemNum = num;
}


