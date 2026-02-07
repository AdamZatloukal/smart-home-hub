import { useState } from "react";
import { Image, Pressable, Switch, Text, View } from "react-native";
import { styles } from "../styles/DashboardLight";

type DashboardProps = {
    catchphrase: string
}

function DashboardLight({ catchphrase }: DashboardProps) {
    const [isEnabled, setIsEnabled] = useState(false);
    const [isFavourite, setIsFavourite] = useState(false);

    const heartImages = {
        empty: require("../assets/images/heart-empty.png"),
        filled: require("../assets/images/heart-filled.png")
    };

    function toggleSwitch() {
        // add fetch
        setIsEnabled(!isEnabled)
    }

    return (
        <View style={styles.dashboard}>
            <View style={styles.titleContainer}>
                <Text style={styles.catchphrase}>{catchphrase}</Text>
                <View style={styles.dashboardContainer}>
                    <View style={styles.dashboardMain}>
                        <Text style={styles.colorTitleText}>Aktuální barva</Text>
                        <Text style={styles.colorText}>#FFFFFF</Text>
                    </View>
                    <View style={styles.dashboardColor}>
                        <View style={styles.heartContainer}>
                            <Pressable
                                onPress={() => {
                                    setIsFavourite(!isFavourite)
                                }}
                            >
                                <Image source={heartImages[isFavourite ? "filled" : "empty"]}></Image>
                            </Pressable>
                        </View>
                        <View style={styles.switchContainer}>
                            <Switch
                                onValueChange={toggleSwitch}
                                value={isEnabled}
                                style={{ transform: [{ scaleX: 1.3 }, { scaleY: 1.3 }] }}
                            />
                        </View>
                    </View>
                </View>
            </View>
        </View>
    )
}

export default DashboardLight;