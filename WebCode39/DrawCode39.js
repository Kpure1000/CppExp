var cvs = document.getElementById("canv");
var chk = document.getElementById("checker");
var strIn = document.getElementById("inputer");

var ctx = cvs.getContext("2d");

var xpos_org = cvs.width * 0.1;
var xpos = xpos_org;
var ypos = cvs.height * 0.2;

var wfat = 6.0;
var tfat = 2.0;
var yfat = cvs.height * 0.5;

// var code = [0x06, 0x11, 0x09, 0x18, 0x05, 0x14, 0x0c, 0x03, 0x12, 0x0a];

var code39 = [
    0x34, 0x121, 0x61, 0x160, 0x31, 0x130, 0x70, 0x25, 0x124, 0x64, // 0-9
    0x109, 0x49, 0x148, 0x19, 0x118, 0x58, 0xd, // a-g
    0x10c, 0x4c, 0x1c, 0x103, 0x43, 0x142, 0x13, // h-n
    0x112, 0x52, 0x7, // o-q
    0x106, 0x46, 0x16, // r-t
    0x181, 0xc1, 0x1c0, // u-w
    0x91, 0x190, 0xd0, // x-z
    0x85, 0x184, 0xc4, 0x94, 0xa8, 0xa2, 0x8a, 0x2a // 
];

var outCode = [];

var _FAT_ = 1,
    _THIN_ = 2,
    _FILL_ = 3,
    _VOID_ = 4,
    _SPLIT_ = 5;


function doDraw() {
    ctx.clearRect(0, 0, cvs.width, cvs.height);
    xpos = xpos_org;
    outCode.splice(0, outCode.length);

    var inStr = strIn.value;
    inStr = inStr.toUpperCase();

    //  checking code
    if (chk.checked == true) {
        var codeTotalNum = 0;
        for (var i = 0, len = inStr.length; i < len; i++) {
            codeTotalNum += GetIndex(inStr[i]);
        }
        codeTotalNum %= 44;
        inStr += GetChar(codeTotalNum);
    }

    //  starting code
    inStr = '*' + inStr;
    //  ending code
    inStr += '*';
    ctx.font = "22px Arial";
    ctx.fillText(inStr, xpos, 20 + ypos + yfat);
    //  mid code
    var orgL = 0;
    var isFill = true;
    var cCode;
    for (var i = 0, len = inStr.length; i < len; i++) {
        orgL = GetValue(inStr[i]);
        cCode = 0x100;
        isFill = true;
        for (var j = 0; j < 9; j++) {
            outCode.push(((orgL & cCode) >> (8 - j) ? _FAT_ : _THIN_) *
                (isFill ? _FILL_ : _VOID_));
            cCode >>= 1;
            isFill = !isFill;
        }
        outCode.push(_THIN_ * _VOID_);
    }

    //  draw
    for (var i = 0, len = outCode.length; i < len; i++) {
        switch (outCode[i]) {
            case 3:
                Draw(true, true);
                break;
            case 4:
                Draw(true, false);
                break;
            case 5:
                DrawSplit();
                break;
            case 6:
                Draw(false, true);
                break;
            case 8:
                Draw(false, false);
                break;
            default:
                break;
        }
    }
}

function GetChar(numIn) {
    if (numIn >= 0 && numIn <= 9) {
        return String.fromCharCode('0'.charCodeAt() + numIn);
    } else if (numIn >= 10 && numIn <= 10 + 'Z'.charCodeAt() - 'A'.charCodeAt()) {
        return String.fromCharCode('A'.charCodeAt() + numIn - 10);
    } else {
        switch (numIn) {
            case 36:
                return '-';
            case 37:
                return '.';
            case 38:
                return ' ';
            case 39:
                return '*';
            case 40:
                return '$';
            case 41:
                return '/';
            case 42:
                return '+';
            case 43:
                return '%';
            default:
                return ' ';
        }
    }
}

function GetIndex(chIn) {
    if (chIn >= '0' && chIn <= '9') {
        return chIn.charCodeAt() - '0'.charCodeAt();
    } else if (chIn >= 'A' && chIn <= 'Z') {
        return chIn.charCodeAt() - 'A'.charCodeAt() + 10;
    } else {
        switch (chIn) {
            case '-':
                return 36;
            case '.':
                return 37;
            case ' ':
                return 38;
            case '*':
                return 39;
            case '$':
                return 40;
            case '/':
                return 41;
            case '+':
                return 42;
            case '%':
                return 43;
            default:
                return 36;
        }
    }
}

function GetValue(chIn_org) {
    var index = GetIndex(chIn_org);
    return code39[index];
}

function Draw(_fat, _fill) {
    var tmpW;
    tmpW = _fat ? wfat : tfat;
    ctx.beginPath();
    ctx.fillStyle = "rgba(0, 0, 0, 1.0)";
    if (_fill) {
        ctx.fillRect(xpos, ypos, tmpW, yfat);
    }
    ctx.closePath();
    xpos += _fat ? wfat : tfat;
}