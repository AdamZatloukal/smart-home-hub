import { useState } from "react";
import { Image, Pressable, Switch, Text, View } from "react-native";
import { colorDataType } from "../data/colorData";
import { styles } from "../styles/DashboardLight";
import { saveToStorage } from "../utils/storage";

type DashboardProps = {
    catchphrase: string
    colorHex: string,
    data: colorDataType
    setData: Function
}

function getColor(colorHex: string, data: colorDataType) {
    return data.find((item) => item.color === colorHex)
}

function DashboardLight({ catchphrase, colorHex, data, setData }: DashboardProps) {
    const [isEnabled, setIsEnabled] = useState(false);

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
                        <Text style={styles.colorText}>{colorHex.toUpperCase() ?? "Nelze načíst"}</Text>
                    </View>
                    <View style={[styles.dashboardColor, { backgroundColor: colorHex }]}>
                        <View style={styles.heartContainer}>
                            <Pressable
                                onPress={() => {
                                    const newData = data.map((item) =>
                                        item.color === colorHex ? { ...item, isFavourite: !item.isFavourite } : item
                                    )

                                    setData(newData)
                                    saveToStorage(newData, "colors")
                                }}
                            >
                                <Image source={heartImages[getColor(colorHex, data)?.isFavourite ? "filled" : "empty"]}></Image>
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