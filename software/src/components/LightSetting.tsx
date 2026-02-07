import Feather from '@expo/vector-icons/Feather';
import BottomSheet from "@gorhom/bottom-sheet";
import { ReactNode, RefObject } from "react";
import { Pressable, Text, View } from "react-native";
import { styles } from "../styles/LightSetting";

// add flatlist of fav colors, color picker in botoom sheet, other options

type LightSettingProps = {
    name: string
    bottomSheetRef?: RefObject<BottomSheet | null>
    children?: ReactNode,
    setWidget: Function
}

function LightSetting({ name, bottomSheetRef, children, setWidget }: LightSettingProps) {

    return (
        <View style={styles.settingContainer}>
            <View style={styles.settingContainerInner}>
                <Text style={styles.settingName}>{name}</Text>
                {children}
                <Pressable
                    onPress={() => {
                        setWidget(name)
                        bottomSheetRef?.current?.snapToIndex(3)
                    }}
                    style={styles.expandIcon}
                >
                    <Feather name="arrow-right" size={32} color="black" />
                </Pressable>
            </View>
        </View>
    )
}

export default LightSetting