import { Image, Text, View } from "react-native";
import { styles } from "../styles/Dashboard";

type DashboardProps = {
    welcomeTitle: string,
    catchphrase: string
}

function Dashboard({welcomeTitle, catchphrase}: DashboardProps) {
    return (
        <View style={styles.dashboard}>
            <View style={styles.titleContainer}>
                <Text style={styles.welcomeTitle}>{welcomeTitle}</Text>
                <Text style={styles.catchphrase}>{catchphrase}</Text>
                <Image
                    source={require("../assets/images/dashboard-placeholder.jpg")}
                    style={styles.container}
                ></Image>
            </View>
        </View>
    )
}

export default Dashboard;