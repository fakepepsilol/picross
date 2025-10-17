
plugins {
    application
    alias(libs.plugins.kotlin.jvm)

    id("com.gradleup.shadow") version "9.0.2"
}

repositories {
    mavenCentral()
}

dependencies {
    implementation("com.squareup.okio:okio:2.4.0")
//    implementation(libs.guava)
}

java {
    toolchain {
        languageVersion = JavaLanguageVersion.of(21)
    }
}

application {
    mainClass = "rs.fpl.MainKt"
}
