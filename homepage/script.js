document.addEventListener('DOMContentLoaded', function() {

    function generateBinaryCode() {
        var binaryCode = "";

        for (let i = 0; i < 8*16; i++) {
            var bit = Math.round(Math.random());

            binaryCode += (bit);
        }

        binaryCode += "\n";

        return binaryCode;
    }

    function displayBinaryCode() {
        var binary = generateBinaryCode();
        let object = document.getElementById("hack");
        object.innerHTML = binary;
        console.log(binary);
    }

    setInterval(displayBinaryCode, 100);

});