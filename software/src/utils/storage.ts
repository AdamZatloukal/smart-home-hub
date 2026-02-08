import AsyncStorage from '@react-native-async-storage/async-storage';

export async function saveToStorage(data: object, key: string) {
    try {
        const jsonData = JSON.stringify(data);
        await AsyncStorage.setItem(key, jsonData);
        console.log("stored")
    } catch (error) {
        console.log(error)
    }
}

export async function loadFromStorage(key: string) {
    const jsonData = await AsyncStorage.getItem(key);
    console.log("loaded")
    return jsonData ? JSON.parse(jsonData) : null;
}
