package rs.fpl

import okio.Buffer
import okio.InflaterSource
import okio.inflate
import java.util.zip.Inflater
import kotlin.io.encoding.Base64

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

    val bytes: ByteArray = Base64.decode(b64)
    val source = Buffer().apply { write(bytes) }

    val inflaterSource: InflaterSource = source.inflate(Inflater(true))
    val sink = Buffer()
    var bytesRead = 0L
    while(true){
        val ret = inflaterSource.read(sink, Long.MAX_VALUE)
        if(ret < 0) break
        bytesRead += ret
    }
    val output = sink.readByteArray().decodeToString()
    println(output)
}