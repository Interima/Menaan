function openForm(ind)
{
    myListView.opacity = 0;
    jobCreaterForm.visible = true;
    verticalScroll.visible = false;
    verticalScroll2.visible = true;

    jobCreaterForm.pluginIndex = ind;

}

function closeForm()
{
    myListView.opacity = 1;
    jobCreaterForm.visible = false;
    verticalScroll2.visible =false;
    verticalScroll.visible =true;
}
