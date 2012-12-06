function openForm(ind)
{
    myListView.opacity = 0;
    jobCreatorForm.visible = true;
    verticalScroll.visible = false;
    verticalScroll2.visible = true;

    jobCreaterForm.pluginIndex = ind;

}

function closeForm()
{
    myListView.opacity = 1;
    jobCreatorForm.visible = false;
    verticalScroll2.visible =false;
    verticalScroll.visible =true;
}
