.pragma library

var thiz = this;

this.setTimeout = function(){
}

function create(source, fileName) {
    var status = Qt.include(source);

    if (status.status !== 0) {
        console.warn("Failed to load: " + source);
        console.warn(status.exception);
        return;
    }

    var res = ".pragma library\n";
    res += "Qt.include(\"" + fileName + "\")\n";
    for (var i in thiz) {
        for (var j in thiz[i]) {
            res += "var " + j + " = " + i +"." + j + ";\n";
        }
    }

    return res;
}
