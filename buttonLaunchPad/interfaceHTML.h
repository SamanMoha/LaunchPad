// !!! FILE GENERATED AUTOMATICALLY FROM index.html AND minify.sh !!!
// !!! DO NOT MODIFY !! 

String handleRootHTML = " <!doctype html><html><head><style>td{text-align:center;font-size:60px;padding-right:10px}span{cursor:pointer}.myDiv{height:100%;width:50%;margin-left:30%;font-size:x-large}.myButton{background-color:#d3d3d3;font-size:x-large;border-radius:2px;box-shadow:2px 2px 2px 1px $grey;padding:10px}.active{background-color:#f08080}.disabled{cursor:not-allowed;color:gray}.modal{display:none;position:fixed;z-index:1;left:0;top:0;width:100%;height:100%;overflow:auto;background-color:#000;background-color:rgba(0,0,0,.4)}.modal-content{background-color:#fefefe;margin:15% auto;padding:20px;border:1px solid #888;width:50%}.close{color:#aaa;float:right;font-size:28px;font-weight:700}.close:focus,.close:hover{color:#000;text-decoration:none;cursor:pointer}.color-cadre{color:#fff;padding:10px;margin-bottom:5px;border-radius:2px}.test{margin:30px}</style><title>IoT into</title></head><body><div class='myDiv'><br><br>Button Input:<script type='text/javascript'>var selectedButton=0;document.write('Bouton actif : '+(selectedButton+1))</script><br><br><form><table><tr><td><span id='l1' onclick='selectLed(0)' name='toggle' value=''>O</span></td><td><span id='l2' onclick='selectLed(1)' name='toggle' value=''>O</span></td><td><span id='l3' onclick='selectLed(2)' name='toggle' value=''>O</span></td><td><span id='l4' onclick='selectLed(3)' name='toggle' value=''>O</span></td><td><span id='l5' onclick='selectLed(4)' name='toggle' value=''>O</span></td><td><span id='l6' onclick='selectLed(5)' name='toggle' value=''>O</span></td><td><span id='l7' onclick='selectLed(6)' name='toggle' value=''>O</span></td><td><span id='l8' onclick='selectLed(7)' name='toggle' value=''>O</span></td></tr><tr><td><span id='b1' class='myButton active' onclick='colorActive(b1,O)'>1</span></td><td><span id='b2' class='myButton' onclick='colorActive(b2,1)'>2</span></td><td><span id='b3' class='myButton' onclick='colorActive(b3,2)'>3</span></td><td><span id='b4' class='myButton' onclick='colorActive(b4,3)'>4</span></td><td><span id='b5' class='myButton' onclick='colorActive(b5,4)'>5</span></td><td><span id='b6' class='myButton' onclick='colorActive(b6,5)'>6</span></td><td><span id='b7' class='myButton' onclick='colorActive(b7,6)'>7</span></td><td><span id='b8' class='myButton' onclick='colorActive(b8,7)'>8</span></td></tr></table></form><br>No LED changed.<div id='myModal' class='modal'><div class='modal-content'><span class='close'>&times;</span><p>Choose a color for your LED</p><form action=''><input type='radio' name='color' value='blue' class='test'> <span class='color-cadre' style='background-color:#6495ed'>Blue</span><br><input type='radio' name='color' value='red' class='test'> <span class='color-cadre' style='background-color:#cd5c5c'>Red</span><br><input type='radio' name='color' value='green' class='test'> <span class='color-cadre' style='background-color:#228b22'>Green</span></form></div></div></div><script type='text/javascript'>function selectLed(d){tab[selectedButton].led.push(d),ledTab[d].on=!0,modal.style.display='block'}function colorActive(d,l){selectedButton=l,document.getElementById(d.id).className+=' active'}var tab=[{id:'b1',led:[]},{id:'b2',led:[]},{id:'b3',led:[]},{id:'b4',led:[]},{id:'b5',led:[]},{id:'b6',led:[]},{id:'b7',led:[]},{id:'b8',led:[]}],ledTab=[{id:'l1',on:!1},{id:'l2',on:!1},{id:'l3',on:!0},{id:'l4',on:!1},{id:'l5',on:!1},{id:'l6',on:!1},{id:'l7',on:!1},{id:'l8',on:!1}],modal=document.getElementById('myModal'),span=document.getElementsByClassName('close')[0];span.onclick=function(){modal.style.display='none'},window.onclick=function(d){d.target==modal&&(modal.style.display='none')}</script></body></html><!-- DO NOT REMOVE THIS BACKSLASH--> \
 " ; 
 