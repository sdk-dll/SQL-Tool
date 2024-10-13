<?
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "database";

$conn = new mysqli($servername, $username, $password, $dbname);

$request = $_GET['request'];
$request_decoded = base64_decode($request);

$response = $conn -> query($request_decoded);

if ($response) {
    while ($row = $response->fetch_assoc()) {
        $data[] = $row;
    }
    
    echo json_encode($data);
} else {
    echo json_encode(["error" => $conn->error]);
}

$conn->close();