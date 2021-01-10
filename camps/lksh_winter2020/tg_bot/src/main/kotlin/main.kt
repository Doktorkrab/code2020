import com.elbekD.bot.Bot

fun main(args: Array<String>) {
    val token = "1380562718:AAGvzsjol3rtj2UZuIuz2PxpcXDFM-DTcX0"
    val username = "Beglov_Kh_bot"
    val bot = Bot.createPolling(username, token)
    bot.onAnyUpdate { update ->
        println("$update")
        if (update.edited_message != null)
            bot.sendMessage(
                update.edited_message!!.chat.id,
                replyTo = update.edited_message!!.message_id,
                text = "РЕДАЧЕРЫ -- ПИДОРАСЫ!!!"
            )
        if (update.message != null)
            bot.sendMessage(
                update.message!!.chat.id,
                replyTo = update.message!!.message_id,
                text = "НУ ЗДАРОВА ЕБАТЬ"
            )
    }
    bot.start()
}