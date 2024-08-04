plugins {
    kotlin("jvm") version "2.0.0"
    application
}

repositories {
    mavenCentral()
}

dependencies {
    testImplementation(kotlin("test"))
}

application {
    mainClass = "MainKt"
}

tasks.test {
    useJUnitPlatform()
}

kotlin {
    jvmToolchain(21)
}

tasks.register<JavaExec>("download") {
    group = "Advent of Code"
    description = "Download the given date's input"

    mainClass = (application.mainClass.get())
    classpath = sourceSets["main"].runtimeClasspath

    doFirst {
        val additionalArgs = project.findProperty("date").toString();
        args = listOf("download") + additionalArgs
    }
}

tasks.register<JavaExec>("solve") {
    group = "Advent of Code"
    description = "Solve the given date"

    mainClass = (application.mainClass.get())
    classpath = sourceSets["main"].runtimeClasspath

    doFirst {
        val additionalArgs = project.findProperty("date").toString();
        args = listOf("solve") + additionalArgs
    }
}

tasks.register<JavaExec>("usage") {
    group = "Advent of Code"
    description = "Print CLI usage"

    mainClass = (application.mainClass.get())
    classpath = sourceSets["main"].runtimeClasspath
    args = listOf("usage")
}