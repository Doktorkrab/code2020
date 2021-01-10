import okhttp3.FormBody
import okhttp3.OkHttpClient
import okhttp3.Request
import java.io.IOException

data class Ejudge(val url: String, var SID: String?) {
    init {

    }
}

fun main(args: Array<String>) {
    val client = OkHttpClient()
    val formData = FormBody.Builder()
        .add("contest_id", "38207")
        .add("role", "0")
        .add("prob_name", "0")
        .add("login", "a1-kharitontsev")
        .add("password", "ymtbnyq7")
        .add("locale_id", "1")
        .add("action_2", "Войти")
        .build()
    val getReq = Request.Builder().url("https://ejudge.lksh.ru/cgi-bin/new-client?contest_id=38206&locale_id=1").build()
    val req = Request.Builder().url("https://ejudge.lksh.ru/cgi-bin/new-client").post(formData)
        .addHeader("Accept-Encoding", "gzip, deflate")
        .addHeader("Accept", "*/*")
        .build()
    client.newCall(getReq).execute().use { response ->
        if (!response.isSuccessful) throw IOException("Unexcepted code $response")
        println(response.body!!.string())
    }
    println("-----------------------------------------")
    client.newCall(req).execute().use { response ->
        if (!response.isSuccessful) throw IOException("Unexcepted code $response")
        println(response.body!!.string())
    }
//    val token = "1380562718:AAGvzsjol3rtj2UZuIuz2PxpcXDFM-DTcX0"
//    val username = "Beglov_Kh_bot"
//    val bot = Bot.createPolling(username, token)
//    val ejudgeHashMap = LinkedHashMap<String, Ejudge>()
//    val lastUrl = LinkedHashMap<Long, String>()
//    bot.chain("/start") { msg ->
//        bot.sendMessage(
//            msg.chat.id, "Send a link to ejudge cgi-bin (e.g. https://ejudge.lksh.ru/cgi-bin)\n" +
//                    "Надеюсь, что вы не дураки"
//        )
//    }.then { msg ->
//        // TODO: add url check
//        lastUrl[msg.chat.id] = msg.text!!
//        bot.sendMessage(msg.chat.id, "Enter a label to ejudge")
//    }.then(isTerminal = true) { msg ->
//        ejudgeHashMap[msg.text!!] = Ejudge(lastUrl[msg.chat.id]!!)
//        bot.sendMessage(msg.chat.id, "Ready to work!")
//    }.build()
//
//    bot.onCommand("/listEjudges") { msg, _ ->
//        bot.sendMessage(msg.chat.id, ejudgeHashMap.toList().joinToString("\n") { "${it.first}: ${it.second.url}" })
//    }
//    bot.start()
}