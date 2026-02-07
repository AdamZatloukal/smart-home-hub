import { StyleSheet } from "react-native";
import { Colors } from "../constants/Colors";
import { Fonts } from "../constants/Fonts";

export const styles = StyleSheet.create({
    screen: {
        flex: 1,
        backgroundColor: "#dcdde1"
    },
    options: {
        flex: 3
    },
    contentContainer: {
        justifyContent:"center",
        padding: 10,
        paddingLeft: 10,
        paddingRight: 10
    },
    backgroundStyles: {
        borderRadius: 30,
        backgroundColor: Colors.settingsCard
    },
    handleStyle: {
        backgroundColor: Colors.bottomSheetLine,
        opacity: 0.7,
        height: 7,
        width: 55,

    },
    container: {
        alignItems: "center",
        justifyContent: "flex-start"
    },
    colorListContainer: {
        justifyContent: 'center',
        alignItems: 'center',
        flex: 1
    },
    brightnessContainer: {
        justifyContent: 'center',
        alignItems: 'center',
        flex: 1,
        margin: 20,
        marginBottom: 40   
    },
    brightnessText: {
        fontFamily: Fonts.normalText,
        fontSize: 15
    },
    favouriteText: {
        margin: 10,
        fontFamily: Fonts.normalText,
        fontSize: 15,
        marginLeft: 25
    }
});