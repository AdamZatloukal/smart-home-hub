import { StyleSheet } from "react-native";
import { Fonts } from "../constants/Fonts";

export const styles = StyleSheet.create({
    roomAddButton: {
        width: 40,
        height: 40,
        justifyContent: "center",
        alignItems: "center",
        borderColor: "black",
        borderRadius: 20,
        borderWidth: 2,
        margin: 5
    },
    roomAddText: {
        fontFamily: Fonts.mediumText,
        fontSize: 20
    }
});