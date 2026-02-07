import { StyleSheet } from "react-native";
import { Fonts } from "../constants/Fonts";

export const styles = StyleSheet.create({
    roomSelectText: {
        fontFamily: Fonts.normalText,
        fontSize: 15
    },
    roomSelectButton: {
        width: 100,
        height: 40,
        borderColor: "black",
        borderWidth: 2,
        borderRadius: 25,
        backgroundColor: "transparent",
        justifyContent: "center",
        alignItems: "center",
        margin: 5
    },
});