var citations = document.getElementsByClassName("citation");

// Only one citation is viewable in the page
var citationdiv;

var cumulativeOffset = function(element) {
    var top = 0, left = 0;
    do {
        top += element.offsetTop  || 0;
        left += element.offsetLeft || 0;
        element = element.offsetParent;
    } while(element);

    return {
        top: top,
        left: left
    };
};

var i;
for (i = 0; i < citations.length; i++)
{
    var citation = citations[i];

    // Create the citation when the user mouses over
    citation.onmouseover = function() {
        var citation_size = cumulativeOffset(this);

        var pos = new Object();
        pos.x = citation_size.left + this.offsetWidth;
        pos.y = citation_size.top - this.offsetHeight;

        var target = this.childNodes[0].getAttribute("href").split('#')[1];
        var targetElement = document.getElementById(target);
        var text = targetElement.childNodes[1].outerHTML;

        createCitation(pos, text);
    };

    citation.onclick = function()
    {
        if (citationdiv != null)
        {
            citationdiv.remove();
        }
    }
}

function createCitation(pos, text)
{
    if (citationdiv != null)
    {
        citationdiv.remove();
    }

    citationdiv = document.createElement('div');

    citationdiv.onmouseleave = function()
    {
        this.remove();
    }

    citationdiv.bShouldDelete = true;
    citationdiv.className = "citation-div";
    citationdiv.style.position = "absolute";
    citationdiv.style.zIndex = 100;
    citationdiv.style.marginLeft 	= 16 + "px";
    citationdiv.style.marginTop 	= 16 + "px";
	citationdiv.style.marginRight 	= 16 + "px";
	citationdiv.style.marginBottom 	= 16 + "px";
    citationdiv.style.left = (pos.x - 16) + "px";
    citationdiv.style.top = (pos.y - 16) + "px";
    citationdiv.innerHTML = text;

    document.body.appendChild(citationdiv);
}
