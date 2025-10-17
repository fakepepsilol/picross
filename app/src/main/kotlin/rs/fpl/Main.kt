package rs.fpl


fun main(){
    print("base64: ")
    val b64: String = readln().trim().toCharArray().map { c ->
        when(c){
            '2' -> '1'
            'a' -> '2'
            '1' -> 'a'
            else -> c
        }
    }.joinToString("")
    println("fixed:  ${b64}")

}