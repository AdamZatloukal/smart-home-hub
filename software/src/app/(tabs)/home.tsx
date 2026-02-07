import Dashboard from "@/src/components/Dashboard";
import RoomAddButton from "@/src/components/RoomAddButton";
import RoomButton from "@/src/components/RoomButton";
import { View } from "react-native";
import ApplianceCard from "../../components/ApplicanceCard";
import { styles } from "../../styles/home";

function Home() {

    return (
        <View style={styles.screen}>
            <Dashboard welcomeTitle="Ahoj," catchphrase="Ryan Gosling"/>
            <View style={styles.roomsContainer}>
                <RoomButton roomName="Kuchyně" />
                <RoomAddButton />
            </View>
            <View style={styles.appliances}>
                <ApplianceCard name="Světlo" href="/light" />
            </View>
        </View>
    )
}

export default Home;