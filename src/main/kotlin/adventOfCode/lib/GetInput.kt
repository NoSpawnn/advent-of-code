package adventOfCode.lib

import java.net.HttpURLConnection
import java.net.URI
import java.nio.file.Files
import java.nio.file.Path
import java.nio.file.Paths
import java.nio.file.StandardCopyOption
import kotlin.io.path.createDirectories

object GetInput {
    private const val ENV_VAR_NAME = "AOC_SESSION_KEY"
    private const val INPUT_BASE_URL = "https://adventofcode.com/%s/day/%s/input"
    private const val USER_AGENT_STR = "github.com/NoSpawnn/advent-of-code"
    private const val INPUTS_DIR = "inputs/%s"
    private const val INPUT_FNAME = "%s.txt"

    @Throws(Exception::class)
    private fun getSessionKey(): String {
        return System.getenv(ENV_VAR_NAME) ?: throw Exception("Session key environment variable is unset")
    }

    @Throws(Exception::class)
    private fun buildRequest(year: String, day: String): HttpURLConnection {
        val reqUrlStr = String.format(INPUT_BASE_URL, year, day)
        val url = URI.create(reqUrlStr).toURL()

        return (url.openConnection() as HttpURLConnection).apply {
            requestMethod = "GET"
            setRequestProperty("User-Agent", USER_AGENT_STR)
            setRequestProperty("Cookie", "session=${getSessionKey()}")
        }
    }

    fun getInputPath(year: String, day: String): Path {
        return Paths.get("", String.format(INPUTS_DIR, year), String.format(INPUT_FNAME, day)).toAbsolutePath()
    }

    @Throws(Exception::class)
    fun download(year: String, day: String) {
        val filePath = getInputPath(year, day)
        filePath.parent.createDirectories()

        if (Files.exists(filePath)) {
            println("!! input file already exists !!")
            return
        }

        val connection = buildRequest(year, if (day[0] == '0') day.substring(1) else day)
        when (val responseCode = connection.responseCode) {
            HttpURLConnection.HTTP_NOT_FOUND -> {
                println("DOWNLOAD ERROR $responseCode - requested input does not exist ($year day $day)")
                return
            }

            HttpURLConnection.HTTP_BAD_REQUEST -> {
                println("DOWNLOAD ERROR $responseCode - is your session key correct?")
                return
            }

            HttpURLConnection.HTTP_OK -> {
                connection.inputStream.use { inputStream ->
                    Files.copy(inputStream, filePath, StandardCopyOption.REPLACE_EXISTING)
                }
                println("File downloaded: $filePath")
            }

            else -> {
                println("DOWNLOAD ERROR $responseCode - ${connection.responseMessage}")
            }
        }
    }
}
