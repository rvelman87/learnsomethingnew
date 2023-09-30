const promptSync = require ("prompt-sync")();
let toContinue: string = "Yes"
let result: number = -1
while(toContinue==="Yes") {
    let firstNum =   parseInt(promptSync("Enter the number   :"))
    let secondNum =  parseInt(promptSync("Enter the number   :"))
    let operation =  promptSync("Operation: Enter A for (+), S for (-), D for /, M for X    :")
    switch(operation) {
        case "A":
            result = firstNum + secondNum
            break;
        case "S":
            result = firstNum - secondNum
            break;
        case "D":
            result = firstNum / secondNum
            break;
        case "M":
            result = firstNum * secondNum        
            break;
    }
    console.log(`${firstNum} ${operation} ${secondNum} result ${result}`)
    let response  = promptSync("Enter Y to continue")
    if (response != "Y") {
        break;
    }

}
