<html>
<head>
  <link href="styled.css" rel= "stylesheet">
  <script src="https://www.gstatic.com/firebasejs/4.13.0/firebase.js"></script>
 <script>
   // Initialize Firebase
   var config = {
     apiKey: "AIzaSyDW9LQ3XVa0GzEl4fAeHBp3grq5SQ0hqRk",
     authDomain: "luggagetrack-7cb6b.firebaseapp.com",
     databaseURL: "https://luggagetrack-7cb6b.firebaseio.com",
     projectId: "luggagetrack-7cb6b",
     storageBucket: "",
     messagingSenderId: "106176775598"
   };
   firebase.initializeApp(config);
 </script>

</head>
<body>

<div id="enter">
  <br><br><br>
  <h3>Enter PNR: </h3></div>
  <input type="number" name="id" id="enter_pnr"/>


  <button onclick="fetch();"  type="submit" value="Track" id="Track"> Submit</button>
  <table id="tbl_users_list" border="1">
   <tr>

    <th>OTP</th>
    <th>Flight</th>
    <th>Contact</th>
    <th>Rfid</th>
    <th>PNR</th>
    <th>Stage2</th>
    <th>Stage1</th>
  </tr>
 </table>



  <script>

  function fetch( ){

    var tblUsers = document.getElementById('tbl_users_list');
    var b= document.getElementById('enter_pnr').value;
    var databaseRef = firebase.database().ref('users/'+b);

    var rowIndex = 1;
    var row= tblUsers.insertRow(rowIndex);
 databaseRef.on('value', function(Snapshot) {
   if(Snapshot.val()==null)
   {
     document.write("User not registered");
   }

    Snapshot.forEach(function(childSnapshot) {
  //  var col = row.insertCell(rowIndex);
    var childKey = childSnapshot.key;
    var childData = childSnapshot.val();
      //document.write("User not registered");
    //document.write(childData.Rfid);
    var childNo = childSnapshot.val();
//   var cell_PNR = row.insertCell(0);
 var cell_RFID = row.insertCell(0);
//   var cell_Flight = row.insertCell(2);
  // var cell_Contact = row.insertCell(3);
   //cell_PNR.appendChild(document.createTextNode(childKey));
    cell_RFID.appendChild(document.createTextNode(childData));
    //cell_Flight.appendChild(document.createTextNode(childData.flight));
  //  cell_Contact.appendChild(document.createTextNode(childData.Rfid));
   //var child = 10
 //document.getElementById("display").innerHTML= childData;
//document.write(childData);
    // var row = tblUsers.insertRow(rowIndex);
    //var cellId = row.insertCell(0);
  //   var cellName = row.insertCell(1);
  //   cellId.appendChild(document.createTextNode(childKey));
     //cellName.appendChild(document.createTextNode(childData.user_name));

     //rowIndex = rowIndex + 1;
     rowIndex = rowIndex + 1;
 });

});

}
 </script>

</body>
</html>
