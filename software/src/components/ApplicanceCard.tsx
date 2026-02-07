import { Colors } from "@/src/constants/Colors";
import { Href, useRouter } from "expo-router";
import React, { useState } from "react";
import { Image, Pressable, Switch, Text, View } from "react-native";
import { PressableProps } from "react-native/Libraries/Components/Pressable/Pressable";
import { Styles } from "../styles/ApplianceCard";


type ApplianceCardProps = PressableProps & {
    name: string,
    href: Href
}

function ApplianceCard({ name, href, ...pressableProps }: ApplianceCardProps) {
    const [isEnabled, setIsEnabled] = useState(false);

    const router = useRouter();

    function toggleSwitch() {
        // add fetch
        setIsEnabled(!isEnabled)
    }

    return (
        <Pressable
            style={({ pressed }) => [
                Styles.card,
                {
                    backgroundColor: pressed ? Colors.applianceCardPressed : Colors.applianceCard,
                    opacity: pressed ? 0.8 : 1
                }]
            }
            onPress={() => {
                router.push(href);
             }}
        >
            <View style={Styles.iconContainer}>
                <Image
                    source={require("../assets/images/light-icon.png")}
                    style={Styles.icon}
                ></Image>
            </View>
            <Text style={Styles.title}>{name}</Text>
            <View style={Styles.visualElement}>
                <View style={Styles.visualElementInner1} />
                <View style={Styles.visualElementInner2} />
            </View>
            <View style={Styles.switchContainer}>
                <Switch
                    onValueChange={toggleSwitch}
                    value={isEnabled}
                    style={{ transform: [{ scaleX: 1.3 }, { scaleY: 1.3 }] }}
                />
            </View>
        </Pressable>
    )
}

export default ApplianceCard;