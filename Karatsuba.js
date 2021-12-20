const mapa = [];
var myArray = [];
var cy1; //arbol 1
var cadena = "";

//Inicia Código
function karatsuba(n1, n2, nivel) {

    if (mapa.length <= nivel || typeof mapa[nivel] === 'undefined') {
        mapa[nivel] = "k(" + n1 + "," + n2 + ")";
    } else {
        mapa[nivel] += " " + "k(" + n1 + "," + n2 + ")";
    }

    if (n1.length < n2.length) {
        var aux = n1;
        n1 = n2;
        n2 = aux;
    }
    if (n1.length == 1 || n2.length == 1) {
        var ans = "0";
        var n = parseInt(n2);
        for (var i = 0; i < n; i++) {
            ans = sumBig(ans, n1);
        }
        return ans;
    }
    var n = n1.length;
    var half = Math.floor(n / 2);
    var a = n1.substr(0, n - half);
    var b = n1.substr(n - half);
    var c = "0", d = n2;
    if (n2.length > half) {
        c = n2.substr(0, n2.length - half);
        d = n2.substr(n2.length - half);
    }
    nivel += 1;
    var ac = karatsuba(a, c, nivel);
    var db = karatsuba(b, d, nivel);
    var ad_plus_bc = subBig(subBig(karatsuba(sumBig(a, b), sumBig(c, d), nivel), ac), db);
    return sumBig(sumBig(ac + ceros(2 * half), ad_plus_bc + ceros(half)), db);
}

function subBig(a, b) {
    var n = a.length;
    var m = b.length;
    b = ceros(n - m) + b;
    var ans = "";
    var carry = 0;

    for (var i = n - 1; i >= 0; i--) {
        var sub = parseInt(a[i]) - parseInt(b[i]) - carry;
        if (sub < 0) {
            sub += 10;
            carry = 1;
        } else
            carry = 0;
        ans = sub.toString() + ans;
    }

    for (let i = 0; i < n; i++) {
        if (ans[i] != '0') {
            ans = ans.substr(i);
            break;
        }
    }
    return ans;
}

function sumBig(a, b) {
    var n = a.length;
    var m = b.length;

    if (n > m) {
        b = ceros(n - m).concat(b);
    } else {
        a = ceros(m - n).concat(a);
        n = m;
    }

    var ans = "";
    var carry = 0;
    for (let i = n - 1; i >= 0; i--) {
        let sum = parseInt(a[i]) + parseInt(b[i]) + carry;
        let cans = (sum % 10);
        ans = cans.toString().concat(ans);
        carry = Math.floor(sum / 10);
    }

    if (carry) {
        ans = carry.toString().concat(ans);
    }

    return ans;
}

function ceros(n) {
    var s = "";
    for (let i = 0; i < n; i++)
        s += "0";
    return s;
}
//Termina código

//Página
function fb(id) {
    n1 = document.getElementById("nuno").value;
    document.getElementById('display1').innerHTML = n1;
    n2 = document.getElementById("ndos").value;
    document.getElementById('display2').innerHTML = "X" + n2;
    document.getElementById('bpasos').style.display = 'inline';
    document.getElementById('display3').innerHTML = "Se multiplicará " + n1 + " X " + n2 + ".";
}

function marcar(id) {
    if (id == 1) {
        Animacion();
    } else {
        alert("Otro caso");
    }
}
//Fin página

function Animacion() {
    var resp=karatsuba(document.getElementById("nuno").value,document.getElementById("ndos").value,0);

    function sleep(ms) {
        return new Promise(resolve => setTimeout(resolve, ms));
    }

    const solve = async () => {
        var exp = "EXPLICACION <br>";
        for (var i = 0; i < mapa.length; i++) {
            const myArray = mapa[i].split(" ");
            for (var j = 0; j < myArray.length; j++) {
                
                exp += "<p  class='Comentarios'><b>"+"Llama a  karatsuba " + myArray[j] + "</b></p>";
                document.getElementById("Explicacion").innerHTML = exp;
                cadena += "<p class='tabMed Texto'><b>" + myArray[j] + "</b></p>";
                document.getElementById("Animacion").innerHTML = cadena;
                await sleep(2000);
            }
            cadena += "<br>";
            
        }
        document.getElementById("Animacion").innerHTML=cadena+"RESULTADO="+resp;
    }

    solve();
}
